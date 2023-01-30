#ifndef WATERLEVELDETECTION_H
#define WATERLEVELDETECTION_H

#include <stdio.h>
#include <cstring>
#include "iWaterlevelDetection.h"
#include "TcpConnection.h"

#define BUFSIZE 100

class WaterlevelDetection : public iWaterlevelDetection
{
	public:
		WaterlevelDetection(TcpConnection tcpConnection);
		~WaterlevelDetection();
		
		

		WaterState GetWaterlevel();
		
	private:
		TcpConnection tcpConnection;
		char buffer[BUFSIZE];
		char recvBuf[BUFSIZE];
		
		WaterlevelDetection(const WaterlevelDetection& other)
			: tcpConnection(other.tcpConnection) { /* do nothing */ };
		WaterlevelDetection& operator= (const WaterlevelDetection&) { return *this; };
};

#endif
