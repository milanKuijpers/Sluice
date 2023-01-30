#ifndef IWATERLEVELDETECTION_H
#define IWATERLEVELDETECTION_H

#include "WaterState.h"

class iWaterlevelDetection
{
	public:
		virtual ~iWaterlevelDetection(){};

		virtual WaterState GetWaterlevel() = 0;
	
};

#endif
