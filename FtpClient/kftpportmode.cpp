#include <memory>
#include <string>

#include "debug.h"
#include "kftpportmode.h"
#include "ktcpsocket.h"

KFtpPortMode::KFtpPortMode() :
	m_portCmdPtr(std::make_shared<std::string>("PORT ")),
	m_port1(20),
	m_port2(31)
{
	m_tcpDataSocketPtr = std::make_shared<KTcpSocket>(KTcpSocket(
		std::string("127.0.0.1"),
		generate_port(m_port1, m_port2)
	));
}

KFtpPortMode::~KFtpPortMode()
{
}

bool KFtpPortMode::startFtpServerListener()
{
	if (m_tcpDataSocketPtr->sockBind())
	{
		// PRINT("[ startFtpServerListener sockBind ok ]");
		if (m_tcpDataSocketPtr->sockListen(3))
		{
			// PRINT("[ startFtpServerListener sockListen ok ]");
			auto ip(m_tcpDataSocketPtr->ip());
			// auto port(m_tcpDataSocketPtr->port());
			// PRINT("port:" + std::to_string(port));
			format_ip_with_comma(ip);
			m_portCmdPtr->append(ip).append(",")
				.append(std::to_string(m_port1)).append(",")
				.append(std::to_string(m_port2)).append("\r\n");

			return true;
		}
	}
	return false;
}

void KFtpPortMode::format_ip_with_comma(std::string &ip)
{
	for (auto it = ip.begin(); it != ip.end(); ++it)
	{
		if ('.' == *it)
		{
			*it = ',';
		}
	}
}

uint16_t KFtpPortMode::generate_port(uint8_t port1, uint8_t port2)
{
	if (port1 > 255)
	{
		port1 = 255;
	}
	if (port2 > 255)
	{
		port2 = 255;
	}
	return port1 * 256 + port2;
}
