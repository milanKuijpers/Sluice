#ifndef IEVENTGENERATOR_H
#define IEVENTGENERATOR_H

#include "Event.h"

class iEventGenerator
{
public:
    virtual ~iEventGenerator() {};

    virtual Event GetEvent() = 0;
};

#endif

