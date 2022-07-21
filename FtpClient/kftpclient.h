#ifndef __K_FTP_CLIENT_H_
#define __K_FTP_CLIENT_H_

#include "ktcpsocket.h"
#include "kftpcommandhandle.h"

class KFtpClient {
public:
	const static int FTP_PORT = 21;

	KFtpClient(const std::string &ip);
	~KFtpClient();
	
	void ftpLogin();
	void runLoop();

	bool connectToFtpServer();
	void waitForConnectServerReply();

private:
	KTcpSocket *m_tcpControlSocket;
	KFtpCommandHandle *m_commandHandle;
};

#endif
