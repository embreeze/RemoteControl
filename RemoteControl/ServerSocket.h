#pragma once
#include "pch.h"
#include "framework.h"

class CServerSocket
{
public:
	static CServerSocket* getInstance()
	{
		if (m_instance == NULL) { // ��̬������û��thisָ�룬�޷�ֱ�ӷ��ʳ�Ա����
			m_instance = new CServerSocket();
		}
		return m_instance;
	}

private:
	CServerSocket& operator=(const CServerSocket& ss) {}
	CServerSocket(const CServerSocket&) {}
	CServerSocket() 
	{
		if (InitSockEnv() == FALSE)
		{
			MessageBox(NULL, _T("�޷���ʼ�����绷��������������ã�"), _T("��ʼ������"), MB_OK | MB_ICONERROR);
			exit(0);
		}
	}

	~CServerSocket()
	{
		WSACleanup();
	}

	BOOL InitSockEnv() {
		WSADATA data;
		if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
		{
			return FALSE;
		}
		else return TRUE;
	}
	static CServerSocket* m_instance;
};

extern CServerSocket server;

