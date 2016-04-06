#include <iostream>
#include "NetConnect.hh"
#include "NetHandler.hh"
#include "InetAddr.hh"
#include "TCPSocket.hh"

using namespace std;

int main()
{

	//TCPSocket* sock = new TCPSocket();
	//sock->setHomeAddr( "127.0.0.1", 8034);
	//sock->Bind();
	//sock->Listen();
	//TCPSocket* sock2 = sock->Accept();

	NetHandler h;
	h.startHandler();	
	

	return 0;
}

