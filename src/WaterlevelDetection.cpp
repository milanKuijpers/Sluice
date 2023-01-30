#include "WaterlevelDetection.h"

WaterlevelDetection::WaterlevelDetection(TcpConnection tcpConnection)
	: tcpConnection(tcpConnection)
{
	strcpy(buffer, "GetWaterLevel;");
}
WaterlevelDetection::~WaterlevelDetection()
{
}

WaterState WaterlevelDetection::GetWaterlevel()

{
	tcpConnection.SendMessage(buffer, recvBuf, BUFSIZE); 
	
	if(strcmp(recvBuf, "low;") == 0)
	{
		return low;
	}
	else if(strcmp(recvBuf, "belowValve2;") == 0)
	{
		return belowValve2;
	}
	else if(strcmp(recvBuf, "aboveValve2;") == 0)
	{
		return aboveValve2;
	}
	else if(strcmp(recvBuf, "aboveValve3;") == 0)
	{
		return aboveValve3;
	}
	else 
	{
		return high;
	}
}
