#ifndef EVENTGENERATOR_H
#define EVENTGENERATOR_H

#include "Event.h"
#include "WaterState.h"
#include "LockState.h"
#include "DoorState.h"
#include "iEventGenerator.h"
#include "Door.h"
#include "iWaterlevelDetection.h"
#include "iUserActions.h"
#include <vector>

class EventGenerator: public iEventGenerator, public iUserActions
{
	public:
		EventGenerator(Door& leftDoor, Door& rightDoor, iWaterlevelDetection& waterlevelDetection);

		Event GetEvent();
		
		// Dirty, I know
		void StartPressed();
		void VrijgevenVoorUitvarenPressed();
		void VrijgevenVoorInvarenPressed();
		void AlarmPressed();
		void HerstelPressed();
		
	private:
		Door& leftDoor;
		Door& rightDoor;
		iWaterlevelDetection& waterlevelDetection;
		std::vector<Event> events;
		
		WaterState waterState;
		WaterState prevWaterState;
		
		DoorState leftDoorState;
		DoorState prevLeftDoorState;
		
		DoorState rightDoorState;
		DoorState prevRightDoorState;
		
		LockState lockState;
		LockState prevLockState;

		void HandlePollEvents();
		void pushNewWaterEvent(WaterState waterState);
		void pushNewLeftDoorEvent(DoorState doorState);
		void pushNewRightDoorEvent(DoorState doorState);
		
		// private copy constructor and assignment operator to prevent making copies
		EventGenerator(const EventGenerator& other)
			: leftDoor(other.leftDoor)
			, rightDoor(other.rightDoor)
			, waterlevelDetection(other.waterlevelDetection) { /* do nothing */ };
		EventGenerator& operator= (const EventGenerator&) { return *this; };
		
};

#endif
