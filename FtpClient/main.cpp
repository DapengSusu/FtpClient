#include <iostream>

#include "kftpclient.h"

int main()
{
	KFtpClient client("127.0.0.1");
	client.runLoop();
	return 0;
}
