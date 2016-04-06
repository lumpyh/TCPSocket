#ifndef NETCONNECT_HH
#define NETCONNECT_HH

#include <thread>
#include <vector>
#include <iostream>
#include "TCPSocket.hh"

using namespace std;

class NetConnect
{
	public:
		NetConnect(	TCPSocket* ); 
		~NetConnect();
		void startTH();
		static void start( NetConnect*);
		void run();
		void stopTH();
		void join();
		bool isRunning();
		

	private:
		TCPSocket* sock;
		static unsigned int id;
		unsigned int ownId;
		thread th;
		vector<char> data;
		bool running;
		void processCommand( string);
		

};


#endif
