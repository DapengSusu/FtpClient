#ifndef __K_LOGIN_PASS_COMMAND_H_
#define __K_LOGIN_PASS_COMMAND_H_

#include "kabstractcommand.h"

class KPassCommand : public KAbstractCommand {
public:
	KPassCommand();
	virtual ~KPassCommand();

	void makePassPacket(std::string &packet, std::list<std::string> &cmdArgs);
	virtual void executeCommand(KTcpSocket *tcpSocket, std::list<std::string> &cmdArgs);
	virtual bool waitForServerReply(KTcpSocket *tcpSocket, std::string &reply) const;
};

#endif
