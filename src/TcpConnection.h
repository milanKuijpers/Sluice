#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h> 

class TcpConnection
{
	public:
		TcpConnection();
		~TcpConnection();
		int CreateSocket(int portno);
		bool SendMessage(const char messageBuf[], char receiveBuf[], int length);
		void ConnectToSim();
		void CloseSocket(int socket);
	
	private:
		int sock;
		int nrOfBytes;
		struct sockaddr_in simulator;
		
		// private copy constructor and assignment operator to prevent making copies	
		//TcpConnection(const TcpConnection&) { /* do nothing */ };
		//TcpConnection& operator= (const TcpConnection&) { return *this; };
};

#endif
	
