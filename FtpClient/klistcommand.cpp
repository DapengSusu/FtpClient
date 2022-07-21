#include "klistcommand.h"
#include "debug.h"
#include "kftpportmode.h"
#include <memory>
#include <unistd.h>

#define DEBUG

KListCommand::KListCommand() :
	m_portModePtr(std::make_shared<KFtpPortMode>(KFtpPortMode()))
{
}

KListCommand::~KListCommand()
{
}

void KListCommand::makeListPacket(std::string &packet, std::list<std::string> &cmdArgs)
{
	packet.append("LIST").append(" ");
	for (auto it = cmdArgs.begin(); it != cmdArgs.end(); ++it)
	{
		packet.append(*it).append(" ");
	}
	packet.pop_back();
	packet += "\r\n";

#ifdef DEBUG
	std::cout << "[ List Command Packet ]: " << packet << std::endl;
#endif
}

void KListCommand::executeCommand(KTcpSocket *tcpSocket, std::list<std::string> &cmdArgs)
{
	if (m_portModePtr->startFtpServerListener())
	{
		PRINT("[ KListCommand::executeCommand startFtpServerListener ok ]");
		auto portCmd(m_portModePtr->portCmd());
		std::string listCmdPacket;
		makeListPacket(listCmdPacket, cmdArgs);
		// PRINT(portCmd);
		tcpSocket->sockSend(portCmd.c_str(), portCmd.length());
		usleep(200 * 1000); // 200ms

		// m_portMode.tcpDataSocket()->sockSend(listCmdPacket.c_str(), listCmdPacket.length());
		tcpSocket->sockSend(listCmdPacket.c_str(), listCmdPacket.length());
	}
}

bool KListCommand::waitForServerReply(KTcpSocket *tcpSocket, std::string &reply) const
{
	char buffer[1024] = { 0 };
	int rbytes;

#ifdef DEBUG
	std::cout << "[ KListCommand::waitForServerReply ]: klist command wait for server reply" << std::endl;
#endif

	rbytes = tcpSocket->sockRecv(buffer, sizeof(buffer));
	if (-1 == rbytes)
	{
		return false;
	}

	reply.append(buffer);

	return true;
}
