#include "EventGenerator.h"
#include <iostream>



EventGenerator::EventGenerator(Door& leftDoor, Door& rightDoor, iWaterlevelDetection& waterlevelDetection)
    : leftDoor(leftDoor)
    , rightDoor(rightDoor)
    , waterlevelDetection(waterlevelDetection)
    , prevRightDoorState(doorClosed)
{
}

Event EventGenerator::GetEvent()
{
    Event result = NoEventOccurred;
    HandlePollEvents();

    if(events.size() > 0)
    {
        result = events[0];
        events.erase(events.begin());
    }

    return result;
}

void EventGenerator::StartPressed()
{
    events.push_back(StartBtnPressed);
    std::cerr << "StartBtnPressed event occurred\n";
}
void EventGenerator::VrijgevenVoorInvarenPressed()
{
    events.push_back(InvarenBtnPressed);
    std::cerr << "VrijgevenVoorInvarenBtnPressed event occurred\n";
}
void EventGenerator::VrijgevenVoorUitvarenPressed()
{
    events.push_back(UitvarenBtnPressed);
    std::cerr << "VrijgevenVoorUitvarenBtnPressed event occurred\n";
}
void EventGenerator::AlarmPressed()
{
    events.push_back(AlarmBtnPressed);
    std::cerr << "AlarmBtnPressed event occurred\n";
}
void EventGenerator::HerstelPressed()
{
    events.push_back(HerstelBtnPressed);
    std::cerr << "HerstelBtnPressed event occurred\n";
}

void EventGenerator::HandlePollEvents()
{   
	waterState = waterlevelDetection.GetWaterlevel();
	leftDoorState = leftDoor.GetState();
	
	rightDoorState = rightDoor.GetState();

	if (waterState != prevWaterState)
	{
		pushNewWaterEvent(waterState);
		prevWaterState = waterState;
	}

	if (leftDoorState != prevLeftDoorState)
	{
		pushNewLeftDoorEvent(leftDoorState);
		prevLeftDoorState = leftDoorState;
	}
    
    if (rightDoorState != prevRightDoorState)
    {
		pushNewRightDoorEvent(rightDoorState);
		prevRightDoorState = rightDoorState;
	}

}

void EventGenerator::pushNewWaterEvent(WaterState waterState)
{
	switch(waterState)
	{
		case low:
			events.push_back(WaterlevelIsLow);
			break;
		case belowValve2:
			// nothing yet
			break;
		case aboveValve2:
			events.push_back(WaterlevelAboveValve2);
			break;
		case aboveValve3:
			events.push_back(WaterlevelAboveValve3);
			break;
		case high:
			events.push_back(WaterlevelIsHigh);
			break;
		default:
			break;
	};
}

void EventGenerator::pushNewLeftDoorEvent(DoorState doorState)
{
	switch(doorState)
	{
		case doorLocked:
			// nothing yet
			break;
		case doorClosed:
			events.push_back(DoorClosed);
			break;
		case doorOpen:
			events.push_back(DoorOpened);
			break;
		case doorClosing:
			// nothing yet
			break;
		case doorOpening:
			// nothing yet
			break;
		case doorStopped:
			events.push_back(DoorStopped);
			break;
		case motorDamage:
			// nothing yet
			break;
		default:
			break;
	}
}

void EventGenerator::pushNewRightDoorEvent(DoorState doorState)
{
	switch(doorState)
	{
		case doorLocked:
			// nothing yet
			break;
		case doorClosed:
			events.push_back(DoorClosed);
			break;
		case doorOpen:
			events.push_back(DoorOpened);
			break;
		case doorClosing:
			// nothing yet
			break;
		case doorOpening:
			// nothing yet
			break;
		case doorStopped:
			events.push_back(DoorStopped);
			break;
		case motorDamage:
			// nothing yet
			break;
		default:
			break;
	}
}
