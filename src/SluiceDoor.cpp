#include "SluiceDoor.h"

SluiceDoor::SluiceDoor(iTrafficLight& outgoingTrafficLight, 
	iTrafficLight& ingoingTrafficLight, 
	Door& door, iValve& bottomValve, 
	iValve& middleValve, iValve& topValve)
		: outgoingTrafficLight(outgoingTrafficLight)
		, ingoingTrafficLight(ingoingTrafficLight)
		, door(door)
		, bottomValve(bottomValve)
		, middleValve(middleValve)
		, topValve(topValve)
		, isIngoingTrafficLightGreen(false)
		, isOutgoingTrafficLightGreen(false)
{
}
	
SluiceDoor::~SluiceDoor()
{
}
	
void SluiceDoor::TurnOutgoingTrafficLightRedOn()
{
	outgoingTrafficLight.TurnRedOn();
}

void SluiceDoor::TurnOutgoingTrafficLightRedOff()
{
	outgoingTrafficLight.TurnRedOff();
}

void SluiceDoor::TurnOutgoingTrafficLightGreenOn()
{
	outgoingTrafficLight.TurnGreenOn();
	isOutgoingTrafficLightGreen = true;
}

void SluiceDoor::TurnOutgoingTrafficLightGreenOff()
{
	outgoingTrafficLight.TurnGreenOff();
	isOutgoingTrafficLightGreen = false;
}

void SluiceDoor::TurnIngoingTrafficLightRedOn()
{
	ingoingTrafficLight.TurnRedOn();
}

void SluiceDoor::TurnIngoingTrafficLightRedOff()
{
	ingoingTrafficLight.TurnRedOff();
}

void SluiceDoor::TurnIngoingTrafficLightGreenOn()
{
	ingoingTrafficLight.TurnGreenOn();
	isIngoingTrafficLightGreen = true;
}

void SluiceDoor::TurnIngoingTrafficLightGreenOff()
{
	ingoingTrafficLight.TurnGreenOff();
	isIngoingTrafficLightGreen = false;
}

void SluiceDoor::TurnAllTrafficLightsRed()
{
	if (isIngoingTrafficLightGreen)
	{
		TurnIngoingTrafficLightGreenOff();
		TurnIngoingTrafficLightRedOn();
	}
	
	if (isOutgoingTrafficLightGreen)
	{
		TurnOutgoingTrafficLightGreenOff();
		TurnOutgoingTrafficLightRedOn();
	}
}

void SluiceDoor::CloseAllValves()
{
	if (bottomValve.GetState() == open)
	{
		bottomValve.Close();
	}
	
	if (middleValve.GetState() == open)
	{
		middleValve.Close();
	}
	
	if (topValve.GetState() == open)
	{
		topValve.Close();
	}
}

void SluiceDoor::OpenBottomValve()
{
	bottomValve.Open();
}

void SluiceDoor::OpenMiddleValve()
{
	middleValve.Open();
}

void SluiceDoor::OpenTopValve()
{
	topValve.Open();
}

void SluiceDoor::OpenDoor()
{
	door.Open();
}

void SluiceDoor::CloseDoor()
{
	door.Close();
}

void SluiceDoor::StopDoor()
{
	door.Stop();
}

void SluiceDoor::Lock()
{
	door.Lock();
}

bool SluiceDoor::HasLock()
{
	return door.HasLock();
}

DoorState SluiceDoor::GetDoorState()
{
	return door.GetState();
}



