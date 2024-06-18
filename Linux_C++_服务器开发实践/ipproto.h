#pragma once
#include<cstdio>
//TCP头定义 20字节
typedef struct _TCP_HEADER
{
	short sSourPort;//源端口号16bit
	short sDestPort;//目的端口号16bit
	unsigned int uiSequNum;//序列号32bit
	unsigned int uiAcknowledgeNum;//确认号32bit
	short sHeaderLenAndFlag;//
	short sWindowSize;
	short sCheckSum;
	short surgentPointer;
}TCP_HEADER,*PTCP_HEADER;


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

}UDP_HEADER, * PUDP_HEADER;