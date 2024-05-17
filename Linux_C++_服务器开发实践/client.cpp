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
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int ret;
	sockaddr_in clientaddr;
	memset(&clientaddr, 0, sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(3333);
	clientaddr.sin_addr.s_addr = inet_addr("192.168.200.130");

	connect(sockfd, (sockaddr*)&clientaddr, sizeof(clientaddr));

	//接受服务端的消息
	char recvbuf[300];
	do
	{
		ret = recv(sockfd, recvbuf, 300, 0);
		if (ret>0)
		{
			//printf("\n recv %d byte.", ret);
			//for (int i = 0; i < ret; i++)
			//{
			//	printf("%c", recvbuf[i]);
			//}
			//printf("\n");
			recvbuf[ret] = '\0';
			printf("\n recv %d byte : %s\n", ret, recvbuf);
		}
		else if (ret == 0)
		{
			puts("\n the server has closed!\n");

		}
		else
		{
			printf("recv failed: %d\n", errno);
			close(sockfd);
			return 1;
		}
	} while (ret>0);
	//发送数据
	char sendbuf[100];
	for (int i = 0; i < 10; i++)
	{
		sprintf(sendbuf, "NO.%d I`m client .hello server! \n", i + 1);
		send(sockfd, sendbuf, strlen(sendbuf), 0);
		memset(sendbuf, 0, sizeof(sendbuf));
	}
	puts("Sending data to the server is finished.\n");
	close(sockfd);
	getchar();
	return 0;
}