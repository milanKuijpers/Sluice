#ifndef LOCKABLEDOOR_H
#define LOCKABLEDOOR_H

#include "Door.h"
#include "LockState.h"
#include <sstream>
#include <cstring>

class LockableDoor : public Door
{
	public:
		LockableDoor(std::string direction, TcpConnection tcpConnection, bool lock);
		~LockableDoor();
		void Open();
		bool HasLock();

	
	private:
		std::string direction;
		TcpConnection tcpConnection;
		char receiveBuf[BUFSIZE];
		char lockBuf[BUFSIZE];
		bool lock;
		
		// private copy constructor and assignment operator to prevent making copies	
		LockableDoor(const LockableDoor& other) : Door(direction, tcpConnection, lock)
		{
			this->direction = other.direction;
			this->tcpConnection = other.tcpConnection;
			this->lock = other.lock;
		}
		LockableDoor& operator= (const LockableDoor&) { return *this; };

};

#endif
