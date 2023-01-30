#ifndef SLUICEDOOR_H
#define SLUICEDOOR_H

#include "iValve.h"
#include "iTrafficLight.h"
#include "Door.h"
#include "DoorState.h"
#include "ValveState.h"

class SluiceDoor
{
	public:
		SluiceDoor(iTrafficLight& outgoingTrafficLight, 
			iTrafficLight& ingoingTrafficLight, 
			Door& door, iValve& bottomValve, 
			iValve& middleValve, iValve& topValve);
		~SluiceDoor();

		void TurnOutgoingTrafficLightRedOn();
		void TurnOutgoingTrafficLightRedOff();
		void TurnOutgoingTrafficLightGreenOn();
		void TurnOutgoingTrafficLightGreenOff();
		void TurnIngoingTrafficLightRedOn();
		void TurnIngoingTrafficLightRedOff();
		void TurnIngoingTrafficLightGreenOn();
		void TurnIngoingTrafficLightGreenOff();
		void TurnAllTrafficLightsRed();
		void CloseAllValves();
		void OpenBottomValve();
		void OpenMiddleValve();
		void OpenTopValve();
		void OpenDoor();
		void CloseDoor();
		void StopDoor();
		bool HasLock();
		void Lock();
		DoorState GetDoorState();

		
	private:
		iTrafficLight& outgoingTrafficLight;
		iTrafficLight& ingoingTrafficLight;
		Door& door;
		iValve& bottomValve;
		iValve& middleValve;
		iValve& topValve;
		
		bool isIngoingTrafficLightGreen;
		bool isOutgoingTrafficLightGreen;
		
};

#endif
