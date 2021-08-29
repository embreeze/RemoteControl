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

	bool InitSocket() {
		if (m_socket == -1) return false;
		sockaddr_in serv_adr;
		memset(&serv_adr, 0, sizeof(serv_adr));
		serv_adr.sin_family = AF_INET;
		serv_adr.sin_addr.s_addr = INADDR_ANY;
		serv_adr.sin_port = htons(9527);

		if (bind(m_socket, (sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) return false;

		if (listen(m_socket, 1) == -1) return false;
		return true;
	}

	bool AcceptClient() {
		sockaddr_in client_adr;
		int cli_sz = sizeof(client_adr);
		m_client = accept(m_socket, (sockaddr*)&client_adr, &cli_sz);
		if (m_client == -1) return false;
		return true;
	}

	int DealCommand() {
		if (m_client == -1) return FALSE;
		char buffer[1024]{};
		while (true)
		{
			int len = recv(m_client, buffer, sizeof(buffer), 0);
			if (len <= 0) return -1;
			// TODO: Handle command
		}
	}

	bool Send(const char* pData, size_t nSize) {
		return send(m_client, pData, nSize, 0) > 0;
	}

private:
	SOCKET m_socket, m_client;
	CServerSocket& operator=(const CServerSocket& ss) {}
	CServerSocket(const CServerSocket& ss) {
		m_socket = ss.m_socket;
		m_client = ss.m_client;
	}
	CServerSocket() 
	{
		m_socket = INVALID_SOCKET;
		m_client = INVALID_SOCKET;
		if (InitSockEnv() == FALSE)
		{
			MessageBox(NULL, _T("无法初始化网络环境！检查网络设置！"), _T("初始化错误"), MB_OK | MB_ICONERROR);
			exit(0);
		}
		m_socket = socket(PF_INET, SOCK_STREAM, 0);
	}

	~CServerSocket()
	{
		closesocket(m_socket);
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

	static void ReleaseInstance() {
		if (m_instance != NULL) {
			CServerSocket* temp = m_instance;
			m_instance = NULL;
			delete temp;
		}
	}
	class CHelper
	{
	public:
		CHelper() {
			CServerSocket::getInstance();
		}
		~CHelper() {
			CServerSocket::ReleaseInstance();
		}
	};
	static CHelper m_helper;
};


