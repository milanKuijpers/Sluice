#ifndef NORMALDOOR_H
#define NORMALDOOR_H
	
#include "iLockable.h"
#include <string>
#include <sstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include "DoorState.h"
#include "TcpConnection.h"
#include <iostream>

#define BUFSIZE 100

class Door : public iLockable
{
	public:
		Door(std::string direction, TcpConnection tcpConnection, bool lock);
		~Door();
		virtual void Open();
		void Close();
		void Stop();
		void Lock();
		void Unlock();
		LockState GetLockState();
		DoorState GetState();
		virtual bool HasLock();
		
	private:
		std::string direction;
		TcpConnection tcpConnection;
		char receiveBuf[BUFSIZE];
		bool lock;
		
		// private copy constructor and assignment operator to prevent making copies
		Door(const Door& other)
			: direction(other.direction)
			, tcpConnection(other.tcpConnection)
			, lock(other.lock) { /* do nothing */ };
		Door& operator= (const Door&) { return *this; };

};

#endif
