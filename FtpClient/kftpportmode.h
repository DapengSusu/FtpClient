#ifndef __K_FTP_PORT_MODE_H_
#define __K_FTP_PORT_MODE_H_

#include <cstdint>
#include <memory>

#include "ktcpsocket.h"
#include "kftpcommandhandle.h"

class KFtpPortMode {
public:
	KFtpPortMode();
	~KFtpPortMode();

	bool startFtpServerListener();

	const KTcpSocket &tcpDataSocket() { return *m_tcpDataSocketPtr; }
	const std::string &portCmd() { return *m_portCmdPtr; }

private:
	std::shared_ptr<KTcpSocket> m_tcpDataSocketPtr;
	std::shared_ptr<std::string> m_portCmdPtr;
	uint8_t m_port1;
	uint8_t m_port2;

	void format_ip_with_comma(std::string &ip);
	uint16_t generate_port(uint8_t port1, uint8_t port2);
};

#endif
