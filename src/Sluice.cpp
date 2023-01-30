#include "Sluice.h"
#include <iostream>

Sluice::Sluice(iWaterlevelDetection& waterlevelDetection,
			iEventGenerator& eventGenerator, SluiceDoor leftSluiceDoor,
			SluiceDoor rightSluiceDoor)
	: waterlevelDetection(waterlevelDetection)
	, eventGenerator(eventGenerator)
	, leftSluiceDoor(leftSluiceDoor)
	, rightSluiceDoor(rightSluiceDoor)
	, currentState(idle)
{
	schuttenState = new Schutten(leftSluiceDoor, rightSluiceDoor);
	OpenDoorWhereWaterlevelIsTheSame();
	IdleEntryActions();
}

Sluice::~Sluice()
{
	delete schuttenState;
	schuttenState = NULL;
}

bool Sluice::Run()
{	
	Event ev;
	while(true)
	{
		ev = eventGenerator.GetEvent();
		HandleEvent(ev);
	}

}

void Sluice::HandleEvent(Event ev)
{
    switch (currentState)
    {
        case emergency:
            currentState = HandleEmergencyState(ev);
            break;
        case idle:
            currentState = HandleIdleState(ev);
            break;
        case schutten:
            currentState = HandleSchuttenState(ev);
            break;

        default:
            // nothing here
            break;
    };
}

State Sluice::HandleIdleState(Event ev)
{
	State nextState = idle;
	
	switch(ev)
	{
		case InvarenBtnPressed:
			IdleExitActions();
			HandleIngoingTrafficLights();
			
			nextState = idle;
			IdleEntryActions();
			break;
		case UitvarenBtnPressed:
			IdleExitActions();
			HandleOutgoingTrafficLights();
			
			nextState = idle;	
			IdleEntryActions();	
			break;
		case StartBtnPressed:
			IdleExitActions();
			
			nextState = schutten;
			SchuttenEntryActions();
			break;
		case DoorStopped:
			OpenDoorWhereWaterlevelIsTheSame();
			break;
		default:
            // nohting here
			break;
	};
	
	return nextState;
}

State Sluice::HandleSchuttenState(Event ev)
{
	State nextState = schutten;
	
	switch(ev)
	{
		case AlarmBtnPressed:
			schuttenState->HaltMovingDoorsAndCloseOpenValves();
			SchuttenExitActions();
			
			nextState = emergency;
			EmergencyEntryActions();
			break;
		default:
			if (ev == NoEventOccurred)
			{
				// do nothing
			}
			else
			{
				schuttenState->HandleEvent(nextState, ev);
				if(nextState != schutten)
				{
					SchuttenExitActions();
					switch(nextState)
					{
						case idle:
							IdleEntryActions();
							break;
						default:
							// nothing here
							break;
					};
				}
			}
			break;
	};
	
	return nextState;
}

State Sluice::HandleEmergencyState(Event ev)
{
	State nextState = emergency;
	
	switch(ev)
	{
		case HerstelBtnPressed:
			EmergencyExitActions();
			
			nextState = schutten;
			break;
		default:
			// nothing here
			break;
	};
	
	return nextState;
}

void Sluice::IdleEntryActions()
{
	// nothing yet
}

void Sluice::IdleExitActions()
{
	// nothing yet
}

void Sluice::SchuttenEntryActions()
{
	waterState = waterlevelDetection.GetWaterlevel();
	
	turnAllTrafficLightsRed();

	schuttenState->SetBeginningSubstate(waterState);
}

void Sluice::SchuttenExitActions()
{
	// nothing yet
}

void Sluice::EmergencyEntryActions()
{

}

void Sluice::EmergencyExitActions()
{
	schuttenState->ResumeOperation();	
}

void Sluice::OpenDoorWhereWaterlevelIsTheSame()
{
	if (waterlevelDetection.GetWaterlevel() == low)
	{
		 leftSluiceDoor.OpenDoor();
	}
	else
	{
		rightSluiceDoor.OpenDoor();
	}
}

void Sluice::HandleOutgoingTrafficLights()
{
	if (leftSluiceDoor.GetDoorState() == doorOpen)
	{
		leftSluiceDoor.TurnOutgoingTrafficLightGreenOn();
		leftSluiceDoor.TurnOutgoingTrafficLightRedOff();
		leftSluiceDoor.TurnIngoingTrafficLightGreenOff();
		leftSluiceDoor.TurnIngoingTrafficLightRedOn();
	}
	else if (rightSluiceDoor.GetDoorState() == doorOpen)
	{
		rightSluiceDoor.TurnOutgoingTrafficLightGreenOn();
		rightSluiceDoor.TurnOutgoingTrafficLightRedOff();
		rightSluiceDoor.TurnIngoingTrafficLightGreenOff();
		rightSluiceDoor.TurnIngoingTrafficLightRedOn();
	}
	else
	{
		std::cout << "The doors aren't open yet" << std::endl;
	}	
}

void Sluice::HandleIngoingTrafficLights()
{
	if (leftSluiceDoor.GetDoorState() == doorOpen)
	{
		leftSluiceDoor.TurnIngoingTrafficLightGreenOn();
		leftSluiceDoor.TurnIngoingTrafficLightRedOff();
		leftSluiceDoor.TurnOutgoingTrafficLightGreenOff();
		leftSluiceDoor.TurnOutgoingTrafficLightRedOn();
	}
	else if (rightSluiceDoor.GetDoorState() == doorOpen)
	{
		rightSluiceDoor.TurnIngoingTrafficLightGreenOn();
		rightSluiceDoor.TurnIngoingTrafficLightRedOff();
		rightSluiceDoor.TurnOutgoingTrafficLightGreenOff();
		rightSluiceDoor.TurnOutgoingTrafficLightRedOn();
	}
	else
	{
		std::cout << "The doors aren't open yet" << std::endl;
	}	
}

void Sluice::turnAllTrafficLightsRed()
{
	leftSluiceDoor.TurnAllTrafficLightsRed();
	rightSluiceDoor.TurnAllTrafficLightsRed();
}


