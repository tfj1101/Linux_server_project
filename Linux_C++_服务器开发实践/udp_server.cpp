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

	//���÷���˵�ַ��Ϣ
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//����udp�׽���
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf("failed socket");
		return -1;
	}

	//�����׽���ѡ��˿ڸ���
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, (socklen_t)sizeof(on));


	//�󶨷���˵�ַ
	ret = bind(sockfd, (sockaddr*)&servaddr, size);
	if (ret<0)
	{
		printf("bind failed");
		return -1;
	}
	while (true)
	{
		printf("waiting data......\n");
		//����data
		ret = recvfrom(sockfd, rbuf, sizeof(rbuf), 0, (sockaddr*)&servaddr, (socklen_t*)&size);
		if (ret < 0)
		{
			perror("recvfrom failed");
		}
		printf("recvfrom data: %s\n", rbuf);

		//����data ---sendto
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