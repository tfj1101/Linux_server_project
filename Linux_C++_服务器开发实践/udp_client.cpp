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

char wbuf[200];
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
	servaddr.sin_addr.s_addr = inet_addr("192.168.200.131");

	//����udp�׽���
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd<0)
	{
		printf("failed socket");
		return -1;
	}

	//�����׽���ѡ��˿ڸ���
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, (socklen_t)sizeof(on));

	//����data
	puts("������data:");
	scanf("%s", wbuf);
	ret = sendto(sockfd, wbuf, sizeof(wbuf), 0, (sockaddr*)&servaddr, size);
	if (ret<0)
	{
		perror("sendto failed");
	}


	//����data
	char rbuf[50];
	ret = recvfrom(sockfd, rbuf, sizeof(rbuf), 0, (sockaddr*)&servaddr, (socklen_t*)&size);
	if (ret<0)
	{
		printf("recvfrom failed");
	}
	printf("recvform data: %s\n", rbuf);


	close(sockfd);
	getchar();
	return 0;
	
}