#ifndef SCHUTTEN_H
#define SCHUTTEN_H

#include "schuttenSubStates.h"
#include "Event.h"
#include "State.h"
#include "iWaterlevelDetection.h"
#include "SluiceDoor.h"
#include "iEventGenerator.h"
#include "Schutten.h"
#include "DoorState.h"
#include "LockState.h"
#include "WaterState.h"


class Schutten
{
	public:
		Schutten(SluiceDoor leftSluiceDoor, SluiceDoor rightSluiceDoor);
		~Schutten();
		
    void SetBeginningSubstate(WaterState waterState);
    void HandleEvent(State& superstate, Event ev);	
	void HaltMovingDoorsAndCloseOpenValves();
	void ResumeOperation();
	
	private:
		SluiceDoor leftSluiceDoor;
		SluiceDoor rightSluiceDoor;
		
		SubState currentSubState;
		
		
		void HandleEvent(Event ev);
		SubState HandleCloseLeftDoorState(Event ev);
		SubState HandleCloseRightDoorState(Event ev);
		SubState HandleOpenLeftDoorState(State& superstate, Event ev);
		SubState HandleOpenRightDoorState(State& superstate, Event ev);
		SubState HandleOpenBottomValveLeftDoorstate(Event ev);
		SubState HandleOpenBottomValveRightDoorState(Event ev);
		SubState HandleOpenMiddleValveRightDoorState(Event ev);
		SubState HandleOpenTopValveRightDoorState(Event ev);
		
        void InitialStateTransitionActions();
		void CloseLeftDoorEntryActions();
		void CloseLeftDoorExitActions();
		void CloseRightDoorEntryActions();
		void CloseRightDoorExitActions();
		void OpenLeftDoorEntryActions();
		void OpenLeftDoorExitActions();
		void OpenRightDoorEntryActions();
		void OpenRightDoorExitActions();
		void OpenBottomValveLeftDoorEntryActions();
		void OpenBottomValveLeftDoorExitActions();
		void OpenBottomValveRightDoorEntryActions();
		void OpenBottomValveRightDoorExitActions();
		void OpenMiddleValveRightDoorEntryActions();
		void OpenMiddleValveRightDoorExitActions();	
		void OpenTopValveRightDoorEntryActions();
		void OpenTopValveRightDoorExitActions();
		
		ValveState leftBottomValveState;
		ValveState rightBottomValveState;
		ValveState rightMiddleValveState;
		ValveState rightTopValveState;
		
		DoorState leftDoorState;
		DoorState rightDoorState;
		
		//private copy constructor and assignment operator to prevent making copies	
		Schutten(const Schutten& other)
			: leftSluiceDoor(other.leftSluiceDoor)
			, rightSluiceDoor(other.rightSluiceDoor) { /* do nothing */ };
		Schutten& operator= (const Schutten&) { return *this; };
		
};

#endif
