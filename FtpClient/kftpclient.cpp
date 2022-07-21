#include <string>
#include <unistd.h>

#include "kftpclient.h"
#include "debug.h"

KFtpClient::KFtpClient(const std::string &ip)
	:m_tcpControlSocket(new KTcpSocket(ip, FTP_PORT))
{
	m_commandHandle = new KFtpCommandHandle(m_tcpControlSocket);
}

KFtpClient::~KFtpClient()
{
	delete m_tcpControlSocket;
	delete m_commandHandle;
}

void KFtpClient::ftpLogin()
{
	std::string userCmd("USER qx");
	std::string passwdCmd("PASS 123");

	if (connectToFtpServer())
	{
		waitForConnectServerReply();

		// USER cmd
		m_commandHandle->executeCommand(userCmd);
		m_commandHandle->waitForCommandReply();

		// PASS cmd
		m_commandHandle->executeCommand(passwdCmd);
		m_commandHandle->waitForCommandReply();
	}
	else
	{
		PRINT("[ connectToFtpServer failed ]");
	}
}

void KFtpClient::runLoop()
{
	std::string cmdBuffer;
	char buffer[32] = { 0 };
	
	ftpLogin();
	
	for(;;)
	{
		cmdBuffer.clear();
		std::cout << "Ftp >";
		std::cin.getline(buffer, 32);
		cmdBuffer = std::string(buffer);
		// PRINT(std::string("cmdBuffer:" + cmdBuffer));

		m_commandHandle->executeCommand(cmdBuffer);
		m_commandHandle->waitForCommandReply();
		break;
	}
}

bool KFtpClient::connectToFtpServer()
{
	return m_tcpControlSocket->connectToHost();
}

void KFtpClient::waitForConnectServerReply()
{
	char buffer[1024] = { 0 };
	int rbytes = m_tcpControlSocket->sockRecv(buffer, sizeof(buffer));

	if (rbytes > 0)
	{
		std::cout << buffer << std::endl;
	}
}
