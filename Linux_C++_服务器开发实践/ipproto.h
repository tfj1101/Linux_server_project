#pragma once
#include<cstdio>
//TCPͷ���� 20�ֽ�
typedef struct _TCP_HEADER
{
	short sSourPort;//Դ�˿ں�16bit
	short sDestPort;//Ŀ�Ķ˿ں�16bit
	unsigned int uiSequNum;//���к�32bit
	unsigned int uiAcknowledgeNum;//ȷ�Ϻ�32bit
	short sHeaderLenAndFlag;//
	short sWindowSize;
	short sCheckSum;
	short surgentPointer;
}TCP_HEADER,*PTCP_HEADER;


//IPͷ���� 20�ֽ�
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

//UDPͷ���� 8�ֽ�
typedef struct _UDP_HEADER
{
	unsigned short m_usSourPort;
	unsigned short m_usDestPort;
	unsigned short m_usLength;
	unsigned short m_usCheckSum;

}UDP_HEADER, * PUDP_HEADER;