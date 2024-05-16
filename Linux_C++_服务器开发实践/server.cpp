#include<sys/socket.h>
#include<cstdio>
#include<assert.h>
#include<errno.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<netdb.h>
#include<string.h>

int main()
{
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	char on = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,&on, sizeof(on));
	int ret;
	ret = bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr));
	if (ret!=0)
	{
		printf("bind failed!\n");
		return 0;
	}
	listen(listenfd, 5);

	sockaddr_in clientaddr;
	socklen_t size = sizeof(clientaddr);

	while (true)
	{
		printf("------waiting for client-------\n");
		int sockfd = accept(listenfd, (sockaddr*)&clientaddr,&size);

		char sendbuf[100];
		for (int i = 0; i < 10; i++)
		{
			//发送数据
			sprintf(sendbuf,"NO. %d welcome to server. Hello client!(client IP: %s )", i + 1, inet_ntoa(clientaddr.sin_addr));
			send(sockfd, sendbuf, sizeof(sendbuf), 0);
		}
		ret = shutdown(sockfd, SHUT_WR);
		//接受数据
		char recvbuf[300];
		do
		{
			ret = recv(sockfd, recvbuf, 300, 0);
			printf("Recv %d byte.  \n", ret);
			if (ret>0)
			{
				recvbuf[ret] = '\0';
				printf("%s \n", recvbuf);
			}
			else if (ret == 0)
			{
				printf("client has closed .\n");
			}
			else
			{
				printf("recv failed with error:%d\n", errno);
				close(sockfd);
				return 1;
			}
		} while (ret>0);
		close(sockfd);
		printf("Continue monitoring? (y/n)\n");
		char ch;
		scanf("%c", &ch);
		if (ch == 'n' or ch == 'N')
			break;
	}
	close(listenfd);
	return 0;
}