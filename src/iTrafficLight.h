#ifndef ITRAFFICLIGH_H
#define ITRAFFICLIGH_H

class iTrafficLight
{
	public:
		virtual ~iTrafficLight(){};

		virtual void TurnGreenOn() = 0;
		virtual void TurnGreenOff() = 0;
		virtual void TurnRedOn() = 0;
		virtual void TurnRedOff() = 0;

};

#endif
