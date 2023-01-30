#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "iTrafficLight.h"
#include "TcpConnection.h"
#include <sstream>
#include <iostream>

#define BUFSIZE 100

class TrafficLight : public iTrafficLight
{
	public:
		TrafficLight(TcpConnection tcpConnection, int number);
		~TrafficLight();
		void TurnGreenOn();
		void TurnGreenOff();
		void TurnRedOn();
		void TurnRedOff();
		
	private:
		TcpConnection tcpConnection;
		int number;
		char receiveBuf[BUFSIZE];
		
		// private copy constructor and assignment operator to prevent making copies	
		TrafficLight(const TrafficLight& other)
			: tcpConnection(other.tcpConnection)
			, number(other.number) { /* do nothing */ };
		TrafficLight& operator= (const TrafficLight&) { return *this; };
};
#endif
