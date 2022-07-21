#include "kusercommand.h"

#define DEBUG

KUserCommand::KUserCommand()
{
}

KUserCommand::~KUserCommand()
{
}

void KUserCommand::makeUserPacket(std::string &packet, std::list<std::string> &cmdArgs)
{
	packet.append("USER").append(" ");
	for (auto it = cmdArgs.begin(); it != cmdArgs.end(); ++it)
	{
		packet.append(*it).append(" ");
	}
	packet.pop_back();
	packet += "\r\n";

#ifdef DEBUG
	std::cout << "[ Login User Command Packet ]: " << packet << std::endl;
#endif
}

void KUserCommand::executeCommand(KTcpSocket *tcpSocket, std::list<std::string> &cmdArgs)
{
	std::string userCmdPacket;
	
	makeUserPacket(userCmdPacket, cmdArgs);
	tcpSocket->sockSend(userCmdPacket.c_str(), userCmdPacket.length());
}

bool KUserCommand::waitForServerReply(KTcpSocket *tcpSocket, std::string &reply) const
{
	char buffer[1024] = { 0 };
	int rbytes;

#ifdef DEBUG
	std::cout << "[ KUserCommand::waitForServerReply ]: kuser command wait for server reply" << std::endl;
#endif

	rbytes = tcpSocket->sockRecv(buffer, sizeof(buffer));
	if (-1 == rbytes)
	{
		return false;
	}

	reply.append(buffer);

	return true;
}
