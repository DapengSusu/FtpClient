#include "kpasscommand.h"

#define DEBUG

KPassCommand::KPassCommand()
{
}

KPassCommand::~KPassCommand()
{
}

void KPassCommand::makePassPacket(std::string &packet, std::list<std::string> &cmdArgs)
{
	packet.append("PASS").append(" ");
	for (auto it = cmdArgs.begin(); it != cmdArgs.end(); ++it)
	{
		packet.append(*it).append(" ");
	}
	packet.pop_back();
	packet += "\r\n";

#ifdef DEBUG
	std::cout << "[ Login Pass Command Packet ]: " << packet << std::endl;
#endif
}

void KPassCommand::executeCommand(KTcpSocket *tcpSocket, std::list<std::string> &cmdArgs)
{
	std::string passCmdPacket;
	
	makePassPacket(passCmdPacket, cmdArgs);
	tcpSocket->sockSend(passCmdPacket.c_str(), passCmdPacket.length());
}

bool KPassCommand::waitForServerReply(KTcpSocket *tcpSocket, std::string &reply) const
{
	char buffer[1024] = { 0 };
	int rbytes;

#ifdef DEBUG
	std::cout << "[ KPassCommand::waitForServerReply ]: kpass command wait for server reply" << std::endl;
#endif

	rbytes = tcpSocket->sockRecv(buffer, sizeof(buffer));
	if (-1 == rbytes)
	{
		return false;
	}

	reply.append(buffer);

	return true;
}
