#ifndef __K_TCP_SOCKET_H_
#define __K_TCP_SOCKET_H_

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class KTcpSocket {
public:
	using SocketHandle = int;
	using SocketAddr = struct sockaddr;

	KTcpSocket(const std::string &ip, uint16_t port);
	~KTcpSocket();

	bool initTcpSocket();
	bool sockBind();
	bool sockListen(int maxRequests);

	bool waitForConntected();

	bool connectToHost();
	bool disconnectFromHost();

	int sockSend(const char *buffer, int len);
	int sockRecv(char *buffer, int maxLen);

	uint16_t port() { return m_port; }
	std::string ip() { return m_ip; }

private:
	SocketHandle m_socket;
	SocketHandle m_clisocket;
	SocketAddr m_cliAddr;
	uint16_t m_port;
	std::string m_ip;
};

#endif
