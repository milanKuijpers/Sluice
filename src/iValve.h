#ifndef IVALVE_H
#define IVALVE_H

#include "ValveState.h"

class iValve
{
	public:
		virtual ~iValve(){};

		virtual void Open() = 0;
		virtual void Close() = 0;
		virtual ValveState GetState() = 0;

};

#endif
