#include "InetAddr.hh"
#include <iostream>

using namespace std;


InetAddr::InetAddr()
{
	memset( &(this->addr), 0, sizeof( this->addr));
	this->addr.sin_family = AF_INET;
}


InetAddr::InetAddr( const InetAddr& obj)
{
	memcpy( &(this->addr), obj.getAddrStruct(), obj.size());
}

InetAddr::InetAddr( const InetAddr* obj)
{
	memcpy( &(this->addr), obj->getAddrStruct(), obj->size());
}

void InetAddr::setIp( string addr)
{
	int stat = inet_aton( addr.c_str(), &(this->addr.sin_addr));
	if( stat == 0)
	cout << "ERROR: IpAddresse " + addr + " wrong format" << endl;
}

string InetAddr::getIp() const
{
	string res( inet_ntoa( this->addr.sin_addr));
	return res;
}

void InetAddr::setPort( in_port_t Port)
{
	this->addr.sin_port = htons( Port);
}

in_port_t InetAddr::getPort() const
{
	return ntohs( this->addr.sin_port);
}

socklen_t InetAddr::size() const
{
	return sizeof( struct sockaddr_in);
}


sockaddr_in* InetAddr::getAddrStruct()
{
	return &(this->addr);
}

const sockaddr_in* InetAddr::getAddrStruct() const
{
	return &(this->addr);
}
