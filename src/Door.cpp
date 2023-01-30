#include "Door.h"


Door::Door(std::string direction, TcpConnection tcpConnection, bool lock)
	: direction(direction)
	, tcpConnection(tcpConnection)
	, lock(lock)
{
}

	
Door::~Door()
{
}

void Door::Open()
{
	std::stringstream os;

	os << "SetDoor"  << direction << ":open;";

	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);	
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to open door" << std::endl;
	}
}

void Door::Close()
{
	std::stringstream os;
	
	os << "SetDoor" << direction << ":close;";

	tcpConnection.SendMessage(os.str().c_str(), receiveBuf,  BUFSIZE);	
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to close door" << std::endl;
	}
}

void Door::Lock()
{
	std::stringstream os;

	os << "SetDoorLock"  << direction << ":on;";

	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);	
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to lock door" << std::endl;
	}	
}

void Door::Unlock()
{
	std::stringstream os;

	os << "SetDoorLock"  << direction << ":off;";

	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);	
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to unlock door" << std::endl;
	}		
}

LockState Door::GetLockState()
{
	std::stringstream os;

	os << "GetDoorLockState"  << direction << ";";

	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);	
	
	
	if (strcmp(receiveBuf, "lockWorking") == 0)
	{
		return lockWorking;
	}
	else
	{
		return lockDamaged;
	}
}

void Door::Stop()
{
	std::stringstream os;

	os << "SetDoor"  << direction << ":stop;";

	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);	
	
	if (strcmp(receiveBuf, "ack;") != 0)
	{
		std::cout << "Failed to stop door" << std::endl;
	}	
}

DoorState Door::GetState()
{
	std::stringstream os;

	os << "GetDoor"  << direction << ";";
	
	tcpConnection.SendMessage(os.str().c_str(), receiveBuf, BUFSIZE);
	
	if(strcmp(receiveBuf, "doorLocked;") == 0)
	{
		return doorClosed;
	}
	else if(strcmp(receiveBuf, "doorClosed;") == 0)
	{
		return doorClosed;
	}
	else if(strcmp(receiveBuf, "doorOpen;") == 0)
	{
		return doorOpen;
	}
	else if(strcmp(receiveBuf, "doorClosing;") == 0)
	{
		return doorClosing;
	}
	else if(strcmp(receiveBuf, "doorOpening;") == 0)
	{
		return doorOpening;
	}
	else if(strcmp(receiveBuf, "doorStopped;") == 0)
	{
		return doorStopped;
	}
	else
	{
		return motorDamage;
	}
}

bool Door::HasLock()
{
	return lock;
}

