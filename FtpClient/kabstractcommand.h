#ifndef __K_ABSTRACT_COMMAND_H_
#define __K_ABSTRACT_COMMAND_H_

#include <iostream>
#include <list>

#include "ktcpsocket.h"

class KAbstractCommand {
public:
	KAbstractCommand();
	virtual ~KAbstractCommand();

	virtual void executeCommand(KTcpSocket* ptcpSocket, std::list<std::string> &cmdArgs) = 0;
	virtual bool waitForServerReply(KTcpSocket *ptcpsocket, std::string &reply) const = 0;
};

#endif
