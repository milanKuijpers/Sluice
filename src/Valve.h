#ifndef VALVE_H
#define VALVE_H

#include "iValve.h"
#include "TcpConnection.h"
#include "string.h"
#include "ValveState.h"
#include <sstream>
#include <stdio.h>
#include <iostream>

#define BUFSIZE 100

class Valve : public iValve
{
	public:
		Valve(TcpConnection tcpConnection, int number, std::string direction);
		~Valve();

		void Open();
		void Close();
		ValveState GetState();
		
	private:
			TcpConnection tcpConnection;
			int number;
			std::string direction;
			char valveBuf[BUFSIZE];
			char receiveBuf[BUFSIZE];
			
			// private copy constructor and assignment operator to prevent making copies	
			Valve(const Valve& other)
				: tcpConnection(other.tcpConnection)
				, direction(other.direction) { /* do nothing */ };
			Valve& operator= (const Valve&) { return *this; };
};

#endif
