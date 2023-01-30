#ifndef SLUICE_H
#define SLUICE_H

#include "Event.h"
#include "State.h"
#include "iWaterlevelDetection.h"
#include "SluiceDoor.h"
#include "iEventGenerator.h"
#include "Schutten.h"
#include "DoorState.h"
#include "LockState.h"
#include "WaterState.h"
#include "ValveState.h"

class Sluice
{
	public:
		Sluice(iWaterlevelDetection& waterlevelDetection,
			iEventGenerator& eventGenerator, SluiceDoor leftSluiceDoor,
			SluiceDoor rightSluiceDoor);
		~Sluice();
		bool Run();
		
	
	private:
		iWaterlevelDetection& waterlevelDetection;
		iEventGenerator& eventGenerator;
		SluiceDoor leftSluiceDoor;
		SluiceDoor rightSluiceDoor;
		Schutten* schuttenState;
		
		State currentState;
		WaterState waterState;
		
		void HandleEvent(Event ev);
		State HandleSchuttenState(Event ev);
		State HandleEmergencyState(Event ev);
		State HandleIdleState(Event ev);
		
		void SchuttenEntryActions();
		void SchuttenExitActions();
		void EmergencyEntryActions();
		void EmergencyExitActions();
		void IdleEntryActions();
		void IdleExitActions();
		
		void OpenDoorWhereWaterlevelIsTheSame();
		void HandleIngoingTrafficLights();
		void HandleOutgoingTrafficLights();
		void turnAllTrafficLightsRed();

		
};

#endif
