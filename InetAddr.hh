#ifndef INETADDR_HH
#define INETADDR_HH 42

#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>

using namespace std;

class InetAddr
{
	public:
		InetAddr();
		
		InetAddr( const InetAddr&);
		InetAddr( const InetAddr*);
		void setIp( string addr);
		string getIp() const;
		void setPort( in_port_t Port);
		in_port_t getPort() const;
		socklen_t size() const;
		
		sockaddr_in* getAddrStruct();
		const sockaddr_in* getAddrStruct() const;
		

	private:
		sockaddr_in addr;

};



#endif
