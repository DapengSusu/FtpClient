#ifndef __K_OPS_COMMAND_H_
#define __K_OPS_COMMAND_H_

#include <iostream>

#include "kabstractcommand.h"

class KOptsCommand : public KAbstractCommand {
public:
	KOptsCommand();
	~KOptsCommand();

	void makeOptUtf8OnPacket(std::string &packet, std::list<std::string> &cmdArgs);
	virtual void executeCommand(KTcpSocket *ptcpSocket, std::list<std::string> &cmdArgs);
	virtual bool waitForServerReply(KTcpSocket *tcpSocket,std::string &reply) const;
private:
};

#endif
