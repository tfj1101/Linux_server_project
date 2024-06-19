#include<cstdio>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

char rbuf[50];
int main()
{
	int sockfd;
	int size;
	int ret;
	char on = 1;
	sockaddr_in servaddr;
	size = sizeof(servaddr);
	memset(&servaddr, 0, size);

	//设置服务端地址信息
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//创建udp套接字
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf("failed socket");
		return -1;
	}

	//设置套接字选项，端口复用
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, (socklen_t)sizeof(on));


	//绑定服务端地址
	ret = bind(sockfd, (sockaddr*)&servaddr, size);
	if (ret<0)
	{
		printf("bind failed");
		return -1;
	}
	while (true)
	{
		printf("waiting data......\n");
		//接收data
		ret = recvfrom(sockfd, rbuf, sizeof(rbuf), 0, (sockaddr*)&servaddr, (socklen_t*)&size);
		if (ret < 0)
		{
			perror("recvfrom failed");
		}
		printf("recvfrom data: %s\n", rbuf);

		//发送data ---sendto
		char wbuf[] = "hello client";
		printf("sendto data: %s\n", wbuf);
		ret = sendto(sockfd, wbuf, sizeof(wbuf), 0, (sockaddr*)&servaddr, (socklen_t)size);
		if (ret < 0)
		{
			printf("sendto failed");
		}
	}
	

	close(sockfd);
	return -1;
}