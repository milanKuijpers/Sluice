#ifndef ILOCKABLE_H
#define ILOCKALBE_H

#include "LockState.h"

class iLockable
{
	public:
		virtual ~iLockable(){};

		virtual void Lock() = 0;
		virtual void Unlock() = 0;
		virtual LockState GetLockState() = 0; 
		
	private:
	
};

#endif
