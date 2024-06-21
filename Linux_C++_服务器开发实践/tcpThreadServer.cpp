#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<stdio.h>
#include<string.h>
#include<pthread.h>

void* client_process(void* arg)
{
	int recv_len = 0;
	char recv_buf[1024] = "";
	long tmp = (long)arg;
	int connfd = tmp;

	//接收数据
	while (true)
	{
		printf("recv_buf : %s \n", recv_buf);
		send(connfd, recv_buf, sizeof(recv_buf), 0);
	}
	printf("client closed!\n");
	close(connfd);
	return NULL;
}



int main()
{
	unsigned short port = 8888;
	char on = 1;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	pthread_t pid;
	if (sockfd < 0)
	{
		perror("socket failed");
		exit(-1);

	}
	//配置网络信息
	sockaddr_in my_addr;
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//my_addr.sin_addr.s_addr = inet_addr("192.168.200.131");

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	int ret = bind(sockfd, (sockaddr*)&my_addr, sizeof(my_addr));
	if (ret < 0)
	{
		perror("bind failed");
		close(sockfd);
		exit(-1);
	}

	listen(sockfd, 10);

	while (true)
	{
		char client_ip[100] = { 0 };
		sockaddr_in client_addr;
		socklen_t cli_len = sizeof(client_addr);

		printf("waiting client......\n");

		int connfd = connect(sockfd, (sockaddr*)&client_addr, cli_len);
		inet_ntop(AF_INET, &client_addr, client_ip, cli_len);
		printf("--------------------\n");
		printf("client ip = %s ,port = %d \n", client_ip, ntohs(client_addr.sin_port));

		if (connfd>0)
		{
			pthread_create(&pid, NULL, client_process, (void*)connfd);
			pthread_detach(pid);
		}

	}
	close(sockfd);
	return 0;
}