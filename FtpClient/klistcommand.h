#ifndef __K_LIST_COMMAND_H_
#define __K_LIST_COMMAND_H_

#include <memory>

#include "kabstractcommand.h"
#include "kftpportmode.h"

class KListCommand : public KAbstractCommand {
public:
	KListCommand();
	virtual ~KListCommand();

	void makeListPacket(std::string &packet, std::list<std::string> &cmdArgs);
	virtual void executeCommand(KTcpSocket *tcpSocket, std::list<std::string> &cmdArgs);
	virtual bool waitForServerReply(KTcpSocket *tcpSocket, std::string &reply) const;

private:
	std::shared_ptr<KFtpPortMode> m_portModePtr;
};

#endif
