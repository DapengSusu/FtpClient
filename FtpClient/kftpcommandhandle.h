#ifndef __K_FTP_COMMAND_HANDLE_H_
#define __K_FTP_COMMAND_HANDLE_H_

#include <list>
#include <map>

#include "ktcpsocket.h"
#include "kabstractcommand.h"

class KFtpCommandHandle {
public:
	KFtpCommandHandle(KTcpSocket* ptcpsocket);
	~KFtpCommandHandle();
	
	void executeCommand(const std::string &cmdString);
	bool waitForCommandReply() const;

	void parseCommand(const std::string &cmdString);
	
	void initCommandMaps();
	void releaseCommandMaps();

private:
	KTcpSocket *m_ptcpSocket;
	KAbstractCommand *m_pcommand;

	std::string m_cmdName;
	std::list<std::string> m_cmdArgs;
	std::map<std::string, KAbstractCommand *> m_commandMap;
};

#endif
