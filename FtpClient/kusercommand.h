#ifndef __K_LOGIN_USER_COMMAND_H_
#define __K_LOGIN_USER_COMMAND_H_

#include "kabstractcommand.h"

class KUserCommand : public KAbstractCommand {
public:
	KUserCommand();
	virtual ~KUserCommand();

	void makeUserPacket(std::string &packet, std::list<std::string> &cmdArgs);
	virtual void executeCommand(KTcpSocket *tcpSocket, std::list<std::string> &cmdArgs);
	virtual bool waitForServerReply(KTcpSocket *tcpSocket, std::string &reply) const;
};

#endif
