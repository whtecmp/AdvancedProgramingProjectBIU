/**************************************
 * Names: Avi Kadria and Efraim Vagner
 * Ids  : 211991401  and 207304262
 **************************************/
#ifndef _H_GURD_SOCKET
#define _H_GURD_SOCKET
#include<iostream>    //cout
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<string>  //std::string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent


namespace AdvancedProgramingProjectBIU {
    /**
    TCP Client class
    */
    class Socket {
    private:
        int sock;
        std::string address;
        int port;
        struct sockaddr_in server;

    public:
        Socket();

        bool Connect(std::string, int);

        bool SendData(std::string data);

        std::string Receive(int);
    };

    
};

#endif