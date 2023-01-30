#include "TrafficLight.h"
#include "string.h"


TrafficLight::TrafficLight(TcpConnection tcpConnection, int number)
	: tcpConnection(tcpConnection)
	, number(number)
{
}
TrafficLight::~TrafficLight()
{
}

void TrafficLight::TurnGreenOn()
{
	std::stringstream os;
	
	os << "SetTrafficLight" << number << "Green:on;";
	
	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to set trafficlight green on" << std::endl;
	}
}
void TrafficLight::TurnGreenOff()
{
	std::stringstream os;
	
	os << "SetTrafficLight" << number << "Green:off;";
	
	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to set trafficlight green off" << std::endl;
	}
}

void TrafficLight::TurnRedOn()
{
	std::stringstream os;
	
	os << "SetTrafficLight" << number << "Red:on;";
	
	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to set trafficlight red on" << std::endl;
	}
}
void TrafficLight::TurnRedOff()
{
	std::stringstream os;
	
	os << "SetTrafficLight" << number << "Red:off;";
	
	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to set trafficlight red off" << std::endl;
	}
}

