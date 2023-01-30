#include "LockableDoor.h"

LockableDoor::LockableDoor(std::string direction, TcpConnection tcpConnection, bool lock) : Door(direction, tcpConnection, lock)
{
	this->direction = direction;
	this->tcpConnection = tcpConnection;
	this->lock = lock;
}

LockableDoor::~LockableDoor()
{
}

void LockableDoor::Open()
{
	Unlock();
	
	std::stringstream os;

	os << "SetDoor"  << direction << ":open;";

	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);		
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to open door" << std::endl;
	}	
	
}

bool LockableDoor::HasLock()
{
	return lock;
}






