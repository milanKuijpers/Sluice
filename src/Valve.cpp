#include <string>
#include <sstream>
#include "Valve.h"
#include "string.h"

Valve::Valve(TcpConnection tcpConnection, int number, std::string direction)
	:tcpConnection(tcpConnection)
	, number(number)
	, direction(direction)	
{
}
Valve::~Valve()
{
}

void Valve::Open()
{
	std::stringstream os;

	os << "SetDoor"  << direction << "Valve" << number << ":open;";

	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to open valve" << std::endl;
	}
	
}
void Valve::Close()
{
	std::stringstream os;	

	os << "SetDoor" << direction << "Valve" << number << ":close;";

	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to close valve" << std::endl;
	}
}

ValveState Valve::GetState()
{
	std::stringstream os;	

	os << "GetDoor" << direction << "Valve" << number << ";";

	tcpConnection.SendMessage(os.str().c_str(), valveBuf, BUFSIZE);	
	
	if (strcmp(valveBuf, "closed;") == 0)
	{
		return closed;
	}
	else
	{
		return open;
	}
}



