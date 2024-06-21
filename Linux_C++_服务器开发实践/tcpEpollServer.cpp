//实现一个简单epoll服务器

#include<ctype.h>
#include<cstdio>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>

#define PORT 8888
#define MAXLINE 80
#define OPEN_MAX 1024

int main(int argc, char* argv[])
{
	int i;
	int j;
	int maxi;
	int listenfd;
	int connfd;
	int sockfd;
	int nready;
	int efd;
	int res;
	ssize_t n;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	socklen_t clilen;
	int client[OPEN_MAX];
	sockaddr_in cliaddr, servaddr;
	epoll_event tep;
	epoll_event ep[OPEN_MAX];

	//网路信息配置

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	if (bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr))<0)
	{
		perror("bind failed");

	}
	if (listen(listenfd, 20) < 0)
	{
		perror("listen failed\n");
	}

	for (int i = 0; i < 5; i++)
	{
		client[i] = -1;
	}
	
	maxi = -1;

	efd = epoll_create(5);

	if (efd<0)
	{
		perror("epoll_create failed\n");
	}
	
	//添加监听套接字
	tep.events = EPOLLIN;
	tep.data.fd = listenfd;
	res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);
	if (res<0)
	{
		perror("epoll_ctl failed");
	}

	while (true)
	{
		nready = epoll_wait(efd, ep, OPEN_MAX, -1);
		if (nready<0)
		{
			perror("epoll_wait");
		}
		for (int i = 0; i < nready; i++)
		{
			//读事件
			if (!(ep[i].events & EPOLLIN))
			{
				continue;
			}
			if (ep[i].data.fd == listenfd)
			{
				//接收客户端
				clilen = sizeof(cliaddr);
				connfd = accept(listenfd, (sockaddr*)&cliaddr, &clilen);
				printf("received from %s at port %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
				for ( j = 0; j < OPEN_MAX; j++)
				{
					if (client[j]<0)
					{
						client[j] = connfd;
						break;
					}

				}
				if (j == OPEN_MAX)
				{
					perror("too many client");
				}
				if (j > maxi)
				{
					maxi = j;
				}
				tep.data.fd = connfd;
				tep.events = EPOLLIN;

				res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);

				if (res < 0)
				{
					perror("epoll_ctl");
				}
			}
			else
			{
				sockfd = ep[i].data.fd;
				n = read(sockfd, buf, MAXLINE);
				if (n == 0)
				{
					for ( j = 0; j <= maxi; j++)
					{
						if (client[j] == sockfd)
						{
							client[j] = -1;
							break;
						}
					}
					res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
					close(sockfd);
					printf("client[%d] closed connection\n", j);
				}
				else
				{
					printf("recive client's data: %s \n", buf);
					for ( j = 0; j < n; j++)
					{
						buf[j] = toupper(buf[j]);
					}
					write(sockfd, buf, n);
				}

			}

		}
	}
	close(listenfd);
	close(efd);
	return 0;
}
