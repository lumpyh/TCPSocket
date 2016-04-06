#include "NetHandler.hh"


NetHandler::NetHandler()
{
}

NetHandler::~NetHandler()
{
	while( !connections.empty())
	{
		connections.back()->stopTH();
		connections.back()->join();
		delete connections.back();
		connections.pop_back();
	}
}

void NetHandler::startHandler()
{
	this->upAndRunning = true;
	this->sock.setHomeAddr( "127.0.0.1", 41337);
	this->sock.Bind();
	this->sock.Listen();
	TCPSocket* s;
	
	while( this->upAndRunning)
	{
		s = this->sock.Accept();
		NetConnect* nc = new NetConnect( s);
		nc->startTH();
		this->connections.push_back( nc); 
	}
}

void NetHandler::stopHandler()
{
	this->upAndRunning = false;
}
