#include "Socket.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>



void Socket::Connect()
{
	targetSock = socket(AF_INET, SOCK_STREAM, 0);
	if (targetSock == -1)
		{std::cout << "Error opening socket" << std::endl; return;}
	
	struct in_addr adress;
	if (!inet_aton(IP.c_str(), &adress))
		{std::cout << "Can't parse IP adress" << std::endl; return}
	
	struct hostnet *server;
	server = gethostbyaddr((const void*)&address, sizeof(address), AF_INET);
	
	if (server == NULL)
		{std::cout<<"Host is unreachable"<<std::endl; return;}
	
	struct sockaddr_in serverAdress;
	bzero((char*)&address, sizeof(adress));
	
	serverAdress.sin_family = AF_INET;
	memcpy((char*)&serverAdress.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
	
	serverAdress.sin_port = htons(port);
	if (connect(targetSock, (struct sockaddr*)&serverAdress, sizeof(serverAdress)) == -1)
		{std::cout<<"Error connecting to server"<<std::endl; return;}
}
	
void Socket::Listen()
{
	mySock = socket(AF_INET, SOCK_STREAM, 0);
	if (mySock == -1)
		{std::cout << "Error opening socket" << std::endl; return;}
	struct sockaddr_in serverAdress;
	bzero((void*)&serverAdress, sizeof(serverAdress));
	
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_addr.s_addr = INADDR_ANY;
	serverAdress.sin_port = htons(port);
	
	if (bind(mySock, (struct sockaddr*)&serverAdress, sizeof(serverAdress)) == -1)
		{std::cout << "Error on binding" << std::endl; return;}
	
	
	
	
	listen(mySock, 1);
	
	struct sockaddr_in clientAdress;
	socklen_t clientAdressLen = sizeof(clientAdress);
	
	targetSock = accept(mySock, (struct sockaddr*)&clientAdress, &clientAdressLen);
	if (targetSock == -1)
		{std::cout << "Error on accept" << std::endl; return;}
		
}
	
void Socket::Send()
{
	char* sending = data.c_str();
	int n = read(targetSock, recived, 512);
	if (n == -1)
		{std::cout<<"Error sending data" << std::endl; return;}
}
	
void Socket::Recive()
{
	char* recived;
	int n = read(targetSock, recived, 512);
	if (n == -1)
		{std::cout<<"Error reciving data" << std::endl; return;}
	data = std::string(recived);
}


Socket::Socket()
{
	std::ifstream settings("settings.txt");
	char temp;
	settings >> temp >> temp >> port >> temp >> temp >> temp >> IP;
}







