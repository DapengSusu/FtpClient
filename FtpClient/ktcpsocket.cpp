#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "ktcpsocket.h"
#include "debug.h"

KTcpSocket::KTcpSocket(const std::string &ip, uint16_t port) :
	m_ip(ip),
	m_port(port),
	m_socket(0),
	m_clisocket(0)
{
	initTcpSocket();
}

KTcpSocket::~KTcpSocket()
{
}

bool KTcpSocket::initTcpSocket()
{
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (-1 == m_socket)
	{
		return false;
	}
	return true;
}

bool KTcpSocket::sockBind()
{
	struct sockaddr_in svrAddr;

	memset(&svrAddr, 0, sizeof(svrAddr));
	svrAddr.sin_family = AF_INET;
	svrAddr.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ip.c_str(), &svrAddr.sin_addr.s_addr);

	auto iRet = bind(m_socket, (struct sockaddr *)&svrAddr, sizeof(svrAddr));
	if (-1 == iRet)
	{
		close(m_socket);
		return false;
	}
	return true;
}

bool KTcpSocket::sockListen(int maxRequests)
{
	auto iRet = listen(m_socket, maxRequests);
	if (-1 == iRet)
	{
		close(m_socket);
		return false;
	}
	return true;
}

bool KTcpSocket::waitForConntected()
{
	std::cout << "[Wait For Connect]" << std::endl;
	m_clisocket = accept(m_socket, (SocketAddr *)&m_cliAddr, (socklen_t *)sizeof(m_cliAddr));
	if (-1 == m_clisocket)
	{
		close(m_socket);
		return false;
	}
	return true;
}

bool KTcpSocket::connectToHost()
{
	struct sockaddr_in svrAddr;

	memset(&svrAddr, 0, sizeof(svrAddr));
	svrAddr.sin_family = AF_INET;
	svrAddr.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ip.c_str(), &svrAddr.sin_addr.s_addr);

	auto iRet = connect(m_socket, (const SocketAddr *)&svrAddr, (socklen_t)sizeof(svrAddr));
	if (-1 == iRet)
	{
		return false;
	}
	return true;
}

bool KTcpSocket::disconnectFromHost()
{
	if (m_socket > 0)
	{
		close(m_socket);
	}
	return true;
}

int KTcpSocket::sockSend(const char *buffer, int len)
{
	return send(m_socket, buffer, len, 0);
}

int KTcpSocket::sockRecv(char *buffer, int maxLen)
{
	return recv(m_socket, buffer, maxLen, 0);
}
