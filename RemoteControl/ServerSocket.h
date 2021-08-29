#pragma once
#include "pch.h"
#include "framework.h"

class CServerSocket
{
public:
	static CServerSocket* getInstance()
	{
		if (m_instance == NULL) { // 静态函数，没有this指针，无法直接访问成员变量
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
			MessageBox(NULL, _T("无法初始化网络环境！检查网络设置！"), _T("初始化错误"), MB_OK | MB_ICONERROR);
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

