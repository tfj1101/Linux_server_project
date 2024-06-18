#include<cstdio>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

char rbuf[500];

//IP头定义 20字节
typedef struct _IP_HEADER
{
	char m_cVersionAndHeaderLen;
	char m_cTypeOfService;
	short m_sTotalLenOfPacket;
	short m_sPacketID;
	short m_sSliceinfo;
	char m_cTTL;
	char m_cTypeOfProtocol;
	short m_sCheckSum;
	unsigned int m_uiSourIp;
	unsigned int m_uiDestIp;

}IP_HEADER, * PIP_HEADER;

//UDP头定义 8字节
typedef struct _UDP_HEADER
{
	unsigned short m_usSourPort;
	unsigned short m_usDestPort;
	unsigned short m_usLength;
	unsigned short m_usCheckSum;

}UDP_HEADER,*PUDP_HEADER;


int main()
{
	int sockfd;
	int size;
	int ret;

	char on = 1;
	sockaddr_in saddr;
	sockaddr_in raddr;

	IP_HEADER iph;
	UDP_HEADER udph;

	size = sizeof(sockaddr_in);

	memset(&saddr, 0, size);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8888);
	saddr.sin_addr.s_addr = inet_addr("192.168.200.131");
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd<0)
	{
		perror("socket failed");
		return -1;
	}
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	//绑定地址信息，ip信息
	ret = bind(sockfd, (sockaddr*)&saddr, size);
	if (ret < 0)
	{
		perror("bind failed");
		getchar();
		return -1;
	}

	int val = sizeof(sockaddr);
	//接收客户端发来的消息
	while (true)
	{
		puts("waiting data......");
		ret = recvfrom(sockfd, rbuf, 500, 0, (sockaddr*)&raddr, (socklen_t*)&val);
		if (ret < 0)
		{
			printf("recvfrom failed: %d ", errno);
			return -1;
		}

		memcpy(&iph, rbuf, 20);
		memcpy(&udph, rbuf + 20, 8);

		int srcp = ntohs(udph.m_usSourPort);
		in_addr ias, iad;
		ias.s_addr = iph.m_uiSourIp;
		iad.s_addr = iph.m_uiDestIp;

		char strdip[50] = "";
		strcpy(strdip, inet_ntoa(iad));
		printf("(sIp = %s ,sPort = %d ),\n (dIp = %s ,dPort = %d )\n", inet_ntoa(ias), ntohs(udph.m_usSourPort), strdip, ntohs(udph.m_usDestPort));
		printf("recv data: %s \n", rbuf + 28);
	}

	close(sockfd);
	return 0;
}
