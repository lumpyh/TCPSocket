#include <iostream>
#include <unistd.h>
#include "InetAddr.hh"
#include "TCPSocket.hh"

using namespace std;

int main()
{

	TCPSocket* sock = new TCPSocket();
	sock->setHomeAddr( "127.0.0.1", 8023);
	sock->setRemoteAddr( "127.0.0.1", 8026);
	sock->Connect();

	cout << "accepted" << endl;
	cout << sock->getRemoteAddr()->getIp() << endl;

	while(1);

	delete sock;

	return 0;
}

