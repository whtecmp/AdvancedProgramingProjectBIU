#ifndef _H_GURD_SERVER
#define _H_GURD_SERVER

#include <string>


class Socket
{
private:

	int mySock;
	int targetSock;
	int port;
	std::string IP;

public:

	void Connect();
	
	void Listen();
	
	void Send();
	
	void Recive();
	
	std::string data;
	
	Socket();

};


#endif /* _H_GURD_SERVER */
