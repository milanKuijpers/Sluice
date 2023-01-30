#include "Schutten.h"

Schutten::Schutten(SluiceDoor leftSluiceDoor, SluiceDoor rightSluiceDoor)
		: leftSluiceDoor(leftSluiceDoor)
		, rightSluiceDoor(rightSluiceDoor)
		, currentSubState(CloseLeftDoor)
{
}

Schutten::~Schutten()
{
}

void Schutten::SetBeginningSubstate(WaterState waterState)
{	
	if (waterState == low)
	{
		CloseLeftDoorEntryActions();
		currentSubState = CloseLeftDoor;
	}
	else
	{
		CloseRightDoorEntryActions();
		currentSubState = CloseRightDoor;
	}	
}

void Schutten::HandleEvent(State& superState, Event ev)
{
	switch(currentSubState)
	{
		case CloseLeftDoor:
			currentSubState = HandleCloseLeftDoorState(ev);
			break;
		case CloseRightDoor:
			currentSubState = HandleCloseRightDoorState(ev);
			break;
		case OpenLeftDoor:
			currentSubState = HandleOpenLeftDoorState(superState, ev);
			break;
		case OpenRightDoor:
			currentSubState = HandleOpenRightDoorState(superState, ev);
			break;
		case OpenBottomValveLeftDoor:
			currentSubState = HandleOpenBottomValveLeftDoorstate(ev);
			break;
		case OpenBottomValveRightDoor:
			currentSubState = HandleOpenBottomValveRightDoorState(ev);
			break;
		case OpenMiddleValveRightDoor:	
			currentSubState = HandleOpenMiddleValveRightDoorState(ev);
			break;
		case OpenTopValveRightDoor:
			currentSubState = HandleOpenTopValveRightDoorState(ev);
			break;
		default:
			// nothing here
			break;
	};
}

void Schutten::HaltMovingDoorsAndCloseOpenValves()
{
	leftDoorState = leftSluiceDoor.GetDoorState();
	rightDoorState  = rightSluiceDoor.GetDoorState();

	leftSluiceDoor.CloseAllValves();
	rightSluiceDoor.CloseAllValves();
	
	if (leftDoorState == doorOpening || leftDoorState == doorClosing)
	{
		leftSluiceDoor.StopDoor();
	}
	
	if (rightDoorState == doorOpening || rightDoorState == doorClosing)
	{
		rightSluiceDoor.StopDoor();
	}
	
}

void Schutten::ResumeOperation()
{

	switch(currentSubState)
	{
		case CloseLeftDoor:
			CloseLeftDoorEntryActions();
			break;
		case CloseRightDoor:
			CloseRightDoorEntryActions();
			break;
		case OpenLeftDoor:
			OpenLeftDoorEntryActions();
			break;
		case OpenRightDoor:
			OpenRightDoorEntryActions();
			break;
		case OpenBottomValveLeftDoor:
			OpenBottomValveLeftDoorEntryActions();
			break;
		case OpenBottomValveRightDoor:
			OpenBottomValveRightDoorEntryActions();
			break;
		case OpenMiddleValveRightDoor:	
			OpenMiddleValveRightDoorEntryActions();
			break;
		case OpenTopValveRightDoor:
			OpenTopValveRightDoorEntryActions();
			break;
		default:
			// nothing here
			break;
	};
}

SubState Schutten::HandleCloseLeftDoorState(Event ev)
{
	SubState nextSubState = CloseLeftDoor;
	
	switch(ev)
	{
		case DoorClosed:
			CloseLeftDoorExitActions();
			
			nextSubState = OpenBottomValveRightDoor;
			OpenBottomValveRightDoorEntryActions();
			break;
		case DoorStopped:
			CloseLeftDoorExitActions();
			
			nextSubState  = CloseLeftDoor;
			CloseLeftDoorEntryActions();			
		default:
			// ignored event
			break;
	};
	
	return nextSubState;
}

SubState Schutten::HandleCloseRightDoorState(Event ev)
{
	SubState nextSubState = CloseRightDoor;
	
	switch(ev)
	{
		case DoorClosed:
			CloseRightDoorExitActions();
			
			nextSubState = OpenBottomValveLeftDoor;
			OpenBottomValveLeftDoorEntryActions();
			break;
		case DoorStopped:
			CloseRightDoorExitActions();
			
			nextSubState = CloseRightDoor;
			CloseRightDoorEntryActions();
			break;
		default:
			// ignored event
			break;
	};
	
	return nextSubState;	
}

SubState Schutten::HandleOpenLeftDoorState(State& superState, Event ev)
{
	SubState nextSubState = OpenLeftDoor;
	
	switch(ev)
	{
		case DoorOpened:
			OpenLeftDoorExitActions();
			superState = idle;
			break;
		case DoorStopped:
			OpenLeftDoorExitActions();
			superState = schutten;
			
			nextSubState = OpenLeftDoor;
			OpenLeftDoorEntryActions();
			break;
		default:
			// ignored event
			break;
	};
	
	return nextSubState;	
}

SubState Schutten::HandleOpenRightDoorState(State& superState, Event ev)
{
	SubState nextSubState = OpenRightDoor;
	
	switch(ev)
	{
		case DoorOpened:
			OpenRightDoorExitActions();
			
			superState = idle;
			break;
		case DoorStopped:
			OpenRightDoorExitActions();
			superState = schutten;
			
			nextSubState = OpenRightDoor;
			OpenRightDoorEntryActions();
			break;
		default:
			// ignored event
			break;
	};
	
	return nextSubState;	
}

SubState Schutten::HandleOpenBottomValveLeftDoorstate(Event ev)
{
	SubState nextSubState = OpenBottomValveLeftDoor;
	
	switch(ev)
	{
		case WaterlevelIsLow:
			OpenBottomValveLeftDoorExitActions();
			
			nextSubState = OpenLeftDoor;
			OpenLeftDoorEntryActions();
			break;
		default:
			// ignored event
			break;
	};
	
	return nextSubState;	
}

SubState Schutten::HandleOpenBottomValveRightDoorState(Event ev)
{
	SubState nextSubState = OpenBottomValveRightDoor;
	
	switch(ev)
	{
		case WaterlevelAboveValve2:
			OpenBottomValveRightDoorExitActions();
			
			nextSubState = OpenMiddleValveRightDoor;
			OpenMiddleValveRightDoorEntryActions();
			break;
		default:
			// ignored event
			break;
	};
	
	return nextSubState;	
}

SubState Schutten::HandleOpenMiddleValveRightDoorState(Event ev)
{
	SubState nextSubState = OpenMiddleValveRightDoor;
	
	switch(ev)
	{
		case WaterlevelAboveValve3:
			OpenMiddleValveRightDoorExitActions();
			
			nextSubState = OpenTopValveRightDoor;
			OpenTopValveRightDoorEntryActions();
			break;
		default:
			// ignored event
			break;
	};
	
	return nextSubState;	
}

SubState Schutten::HandleOpenTopValveRightDoorState(Event ev)
{
	SubState nextSubState = OpenTopValveRightDoor;
	
	switch(ev)
	{
		case WaterlevelIsHigh:
			OpenTopValveRightDoorExitActions();
			
			nextSubState = OpenRightDoor;
			OpenRightDoorEntryActions();
			break;
		default:
			// ignored event
			break;
	};
	
	return nextSubState;	
}

void Schutten::InitialStateTransitionActions()
{
	// nothing yet
}

void Schutten::CloseLeftDoorEntryActions()
{	
	leftSluiceDoor.CloseDoor();
}
void Schutten::CloseLeftDoorExitActions()
{
    if (leftSluiceDoor.HasLock())
    {
		leftSluiceDoor.Lock();
	}
}

void Schutten::CloseRightDoorEntryActions()
{
	rightSluiceDoor.CloseDoor();
}

void Schutten::CloseRightDoorExitActions()
{
	if (rightSluiceDoor.HasLock())
	{
		rightSluiceDoor.Lock();
	}
}

void Schutten::OpenLeftDoorEntryActions()
{
	leftSluiceDoor.OpenDoor();
}

void Schutten::OpenLeftDoorExitActions()
{
	// nothing yet
}

void Schutten::OpenRightDoorEntryActions()
{
	rightSluiceDoor.OpenDoor();
}

void Schutten::OpenRightDoorExitActions()
{
	// nothing yet
}

void Schutten::OpenBottomValveLeftDoorEntryActions()
{
	leftSluiceDoor.OpenBottomValve();
}

void Schutten::OpenBottomValveLeftDoorExitActions()
{
	leftSluiceDoor.CloseAllValves();
}

void Schutten::OpenBottomValveRightDoorEntryActions()
{
	rightSluiceDoor.OpenBottomValve();
}

void Schutten::OpenBottomValveRightDoorExitActions()
{
	// nothing yet
}

void Schutten::OpenMiddleValveRightDoorEntryActions()
{
	rightSluiceDoor.OpenMiddleValve();
}
void Schutten::OpenMiddleValveRightDoorExitActions()	
{
	// nothiing yet
}

void Schutten::OpenTopValveRightDoorEntryActions()
{
	rightSluiceDoor.OpenTopValve();
}

void Schutten::OpenTopValveRightDoorExitActions()
{
	rightSluiceDoor.CloseAllValves();
}
