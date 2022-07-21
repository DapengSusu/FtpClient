#include "koptscommand.h"

#define DEBUG

KOptsCommand::KOptsCommand()
{
}

KOptsCommand::~KOptsCommand()
{
}

void KOptsCommand::makeOptUtf8OnPacket(std::string& packet, std::list<std::string> &cmdArgs)
{
	packet += "OPTS";
	packet += " ";

	for (std::list<std::string>::iterator it = cmdArgs.begin(); it != cmdArgs.end(); ++it)
	{
		packet += *it;
		packet += " ";
	}

	packet += "\r\n";

#ifdef DEBUG
	std::cout << "[ KOptsCommand::makeOptUtf8OnPacket ] : "<< packet << std::endl;
#endif
}

void KOptsCommand::executeCommand(KTcpSocket* ptcpSocket, std::list<std::string> &cmdArgs)
{
	std::string packet;

	makeOptUtf8OnPacket(packet, cmdArgs);
	ptcpSocket->sockSend(packet.c_str(), packet.length());
}

bool KOptsCommand::waitForServerReply(KTcpSocket *tcpSocket, std::string &reply) const
{
	char buffer[1024] = { 0 };
	int rbytes;

#ifdef DEBUG
	std::cout << "[ KOptsCommand::waitForServerReply ]: kopts command wait for server reply" << std::endl;
#endif

	rbytes = tcpSocket->sockRecv(buffer, sizeof(buffer));
	if (-1 == rbytes)
	{
		return false;
	}

	reply.append(buffer);

	return true;
}
