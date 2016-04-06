#include "NetConnect.hh"
#include <cstring>

unsigned int NetConnect::id = 0;

NetConnect::NetConnect( TCPSocket* s):
	running(false),
	sock(s),
	th(),
	ownId( NetConnect::id)
{
	NetConnect::id++;
}

NetConnect::~NetConnect()
{
	delete sock;
}

void NetConnect::startTH()
{
	this->th = thread( NetConnect::start, this);
}

void NetConnect::start( NetConnect* nc)
{
	nc->run();
}


void NetConnect::run()
{
	running = true;
	char* buffer = new char[255];
	memset( buffer, 0, 255);
	ssize_t bufferCount = 0;
	ssize_t count = 0;
	char* pos = NULL;
	bool noSemi = true;
	string command; 
	while( running)
	{
		count = this->sock->Recv( buffer + bufferCount, 255-bufferCount);	
		bufferCount += count < 0 ? 0 : count;
		pos = (char*) memchr( buffer, ';', 255);
		noSemi = pos == NULL ? true : false;
		if( noSemi) continue;
		*pos = '\0';
		command = buffer;
		pos = *(pos+1) == '\n' ? pos+1 : pos;
		memmove( buffer, pos+1, buffer + 255 - pos);
		bufferCount -= (int)  pos -  (int) buffer  + 1;
		memset( buffer + bufferCount, 0, 255 - bufferCount);	
		this->processCommand( command);
	}
	delete[] buffer;
}

void NetConnect::processCommand( string s)
{
	cout << "NC id: " << this->ownId << endl;
	cout << s << endl;
}

bool NetConnect::isRunning()
{
	return this->running;
}

void NetConnect::stopTH()
{
	this->running = false;
}

void NetConnect::join()
{
	this->th.join();
}
