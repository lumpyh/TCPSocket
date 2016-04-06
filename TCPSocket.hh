#ifndef TCPSOCKET_HH
#define TCPSOCKET_HH 42

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <errno.h>
#include <string>

#include "InetAddr.hh"

class TCPSocket
{
	
	public:
		TCPSocket();
		TCPSocket( int, const InetAddr*, const InetAddr*);
		~TCPSocket();
		const InetAddr* getHomeAddr() const;
		const InetAddr* getRemoteAddr() const;
		void setHomeAddr( string, in_port_t);
		void setRemoteAddr( string, in_port_t);
		int Bind();
//		int Bind( char* Addr, in_port_t Port); 
		TCPSocket* Accept();
		void Connect();
		void Listen();
		ssize_t Recv( void*, size_t);
		ssize_t Send( const void*, size_t);
	
	private:
		int socketfd;
		InetAddr* homeAddr;
		InetAddr* remoteAddr;

		
};

#endif
