#include <iostream>
#include "TcpConnection.h"

TcpConnection::TcpConnection()
{
}

TcpConnection::~TcpConnection()
{
}

int TcpConnection::CreateSocket(int port)
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		std::cout << "failed to create socket" << std::endl;
	}
	
	simulator.sin_addr.s_addr = inet_addr("127.0.0.1");
	simulator.sin_family = AF_INET;
	simulator.sin_port = htons(port);
	
	return sock;
}

void TcpConnection::ConnectToSim()
{
	if (connect(sock , (struct sockaddr *)&simulator , sizeof(simulator)) < 0)
	{
		std::cout << "failed to connect to the simulator" << std::endl;
	}	
}

bool TcpConnection::SendMessage(const char messageBuf[], char receiveBuf[], int length)
{
	if (send(sock , messageBuf , length , 0) < 0)
	{
		return false;
	}
	
	nrOfBytes = recv(sock, receiveBuf, length, 0);
	if (nrOfBytes < 0)
	{
		return false;
	}	
	
	receiveBuf[nrOfBytes] = '\0';
	
	return true;
}

void TcpConnection::CloseSocket(int sock)
{
	close(sock);
}
