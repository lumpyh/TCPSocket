#include "TCPSocket.hh"


using namespace std;

TCPSocket::TCPSocket()
{
	this->socketfd = socket( AF_INET, SOCK_STREAM, 0);
	if( this->socketfd < 0)
		cout << "Fehler beim oeffnen des Sockets" << endl;
	this->homeAddr = NULL;
	this->remoteAddr = NULL;
	
}

TCPSocket::TCPSocket( int fd, const InetAddr* hAddr, const InetAddr* rAddr)
{
	this->socketfd = fd;
	this->homeAddr = new InetAddr( hAddr);
	if( rAddr != NULL)
	this->remoteAddr = new InetAddr( rAddr);
}

TCPSocket::~TCPSocket()
{
	shutdown( this->socketfd, 2);
	if( this->homeAddr != NULL)
		delete this->homeAddr;
	if( this->remoteAddr != NULL)
		delete this->remoteAddr;
}

const InetAddr* TCPSocket::getHomeAddr() const
{
	return this->homeAddr;
}

const InetAddr* TCPSocket::getRemoteAddr() const
{
	return this->remoteAddr;
}

void TCPSocket::setHomeAddr( string ip, in_port_t port)
{
	if( this->homeAddr == NULL)
		this->homeAddr = new InetAddr();
	this->homeAddr->setIp( ip);
	this->homeAddr->setPort( port);
}

void TCPSocket::setRemoteAddr( string ip, in_port_t port)
{
	if( this->remoteAddr == NULL)
		this->remoteAddr = new InetAddr();
	this->remoteAddr->setIp( ip);
	this->remoteAddr->setPort( port);
}

int TCPSocket::Bind()
{
	if( this->homeAddr == NULL)
	{
		cout << "HomeAddr not set" << endl;
		return -1;
	}
	int stat = bind( this->socketfd, (struct sockaddr*) this->homeAddr->getAddrStruct(), (this->homeAddr->size()));
	if( stat < 0 )
		cout << "fehler beim bind: " << strerror( errno) <<  endl;
	return 0;
}

//int TCPSocket::Bind( char* Addr, in_port_t Port)
//{
//	this->SetSocketAddr( Addr);
//	this->SetPort( Port);
//	this->Bind();
//
//	return 0;
//}


TCPSocket* TCPSocket::Accept()
{
	socklen_t len = this->remoteAddr->size();
	if( this->remoteAddr == NULL)
		this->remoteAddr = new InetAddr();
	int fd = accept( this->socketfd, (struct sockaddr*) this->remoteAddr->getAddrStruct(), &len);
	TCPSocket* ns = new TCPSocket( fd, this->homeAddr, this->remoteAddr);
	delete this->remoteAddr;
	this->remoteAddr = NULL;
	return ns;
}

void TCPSocket::Connect()
{
	int state = connect( this->socketfd, (struct sockaddr*) this->remoteAddr->getAddrStruct(), sizeof( InetAddr));
	if( state < 0 )
		cout << "fehler beim aton: " << strerror( errno) <<  endl;
}

void TCPSocket::Listen()
{
	int state = listen( this->socketfd, 5);
	if( state < 0 )
		cout << "fehler beim aton: " << strerror( errno) <<  endl;
}

ssize_t TCPSocket::Recv( void* buffer, size_t length)
{
	return recv( this->socketfd, buffer, length, MSG_DONTWAIT);
}

ssize_t TCPSocket::Send( const void* buffer, size_t len)
{
	return send( this->socketfd, buffer, len, 0);
}
