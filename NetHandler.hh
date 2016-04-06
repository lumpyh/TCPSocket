#ifndef NETHANDLER_HH
#define NETHANDLER_HH

#include <iostream>
#include <thread>
#include <vector>
#include "NetConnect.hh"

using namespace std;

class NetHandler
{
	public:	
		NetHandler();
		~NetHandler();
		void startHandler();	
		void stopHandler();
		
	
	private:
		vector<NetConnect*> connections;	
		TCPSocket sock;
		bool upAndRunning;
		

};


#endif
