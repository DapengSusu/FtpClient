#include <string.h>
#include <string>

#include "kftpcommandhandle.h"
#include "kftpportmode.h"
#include "klistcommand.h"
#include "kpasscommand.h"
#include "kusercommand.h"
#include "debug.h"

#define DEBUG

KFtpCommandHandle::KFtpCommandHandle(KTcpSocket* ptcpsocket)
{
	this->m_ptcpSocket = ptcpsocket;
	initCommandMaps();
}
KFtpCommandHandle::~KFtpCommandHandle()
{
	releaseCommandMaps();
}

void KFtpCommandHandle::executeCommand(const std::string &cmdString)
{
	parseCommand(cmdString);
	KAbstractCommand *pcommand = m_commandMap.find(m_cmdName)->second;

#ifdef DEBUG
	std::cout << "[ KFtpCommandHandle::executeCommand ] : command name : " << m_cmdName << std::endl;
	for (auto it = m_cmdArgs.begin(); it != m_cmdArgs.end(); ++it)
	{
		std::cout << "[ KFtpCommandHandle::executeCommand ] : command args : " << *it << std::endl;
	}
#endif
	pcommand->executeCommand(m_ptcpSocket, m_cmdArgs);
}

bool KFtpCommandHandle::waitForCommandReply() const
{
	std::string reply;

#ifdef DEBUG	
	std::cout << "[ KFtpCommandHandle::waitForCommandReply ] : " << m_cmdName << std::endl;
#endif

	KAbstractCommand *pcommand = m_commandMap.find(m_cmdName)->second;
	pcommand->waitForServerReply(m_ptcpSocket, reply);
	std::cout << reply << std::endl;

	return true;
}

void KFtpCommandHandle::parseCommand(const std::string &cmdString)
{
	m_cmdName = cmdString;
	m_cmdArgs.clear();
	std::string cmd(cmdString);
	std::string::size_type pos = 0;
	auto isCmdName = true;
	for (auto index = cmd.find(" ", pos);
		pos <= cmd.length() && index != std::string::npos;
		index = cmd.find(" ", pos))
	{
		if (0 == index)
		{
			++pos;
			continue;
		}
		if (isCmdName)
		{
			m_cmdName = std::string(cmd, pos, index - pos);
			cmd = cmd.substr(index + 1);
			pos = 0;
			isCmdName = false;
			continue;
		}
		m_cmdArgs.emplace_back(std::string(cmd, pos, index - pos));
		pos = index + 1;
	}
	if (false == isCmdName && false == cmd.empty())
	{
		m_cmdArgs.emplace_back(cmd.substr(pos));
	}

#ifdef DEBUG
	std::cout << "[ KFtpCommandHandle::parseCommand ]: command name : " << m_cmdName << std::endl;
	for (auto it = m_cmdArgs.begin(); it != m_cmdArgs.end(); ++it)
	{
		std::cout << "[ KFtpCommandHandle::parseCommand ]: command args : " << *it << std::endl;
	}
#endif
}

void KFtpCommandHandle::initCommandMaps()
{
	m_commandMap.insert(std::make_pair(std::string("USER"), new KUserCommand()));
	m_commandMap.insert(std::make_pair(std::string("PASS"), new KPassCommand()));
	m_commandMap.insert(std::make_pair(std::string("LIST"), new KListCommand()));
}

void KFtpCommandHandle::releaseCommandMaps()
{
	for (auto it = m_commandMap.begin(); it != m_commandMap.end(); ++it)
	{
		delete it->second;
	}
}
