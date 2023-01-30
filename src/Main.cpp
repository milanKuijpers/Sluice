#include <iostream>

#include "DoorState.h"
#include "LockState.h"
#include "State.h"
#include "WaterState.h"
#include "Event.h"
#include "EventGenerator.h"
#include "Schutten.h"
#include "SluiceDoor.h"
#include "WaterlevelDetection.h"
#include "iUserActions.h"
#include "Door.h"
#include "LockableDoor.h"
#include "Valve.h"
#include "TrafficLight.h"
#include "Sluice.h"
#include "TcpConnection.h"
#include <thread>

static void ShowMenu( void )
{
    std::cerr << ("\n\nMenu\n");
    std::cerr << ("====\n");
    std::cerr << ("(1) Start Button\n");
    std::cerr << ("(2) Vrijgeven voor uitvaren button\n");
    std::cerr << ("(3) Vrijgeven voor invaren button\n");
    std::cerr << ("(4) alarm button\n");
    std::cerr << ("(5) herstel button\n");
    std::cerr << ("(6) verander van sluis\n");
    std::cerr << ("-----------------------\n");
    std::cerr << ("(q) QUIT\n");
    std::cerr << ("Choice : ");
}

char GetUserInput()
{
    char choice = '\0';
    std::cin >> choice;
    std::cin.ignore();
    std::cout << "keuze is = " << choice << std::endl;
    return choice;
}

int GetSluice()
{
	std::cout << "Kies uit een van de volgende sluizen : '5555' , '5556' , '5557', 5558' " << std::endl;
	int choice;
	std::cin >> choice;
	std::cin.ignore();
	return choice;
}

int main()
{
	int poort = GetSluice();
	
	// create socket connection 
	TcpConnection tcpConnection;
	int sock_fd = tcpConnection.CreateSocket(poort);
	tcpConnection.ConnectToSim();


	Valve leftBottomValve(tcpConnection, 1, "Left");
	Valve leftMiddleValve(tcpConnection, 2, "Left");
	Valve leftTopValve(tcpConnection, 3, "Left");
	Valve rightBottomValve(tcpConnection, 1, "Right");
	Valve rightMiddleValve(tcpConnection, 2, "Right");
	Valve rightTopValve(tcpConnection, 3, "Right");
	TrafficLight leftIngoingTrafficLight(tcpConnection, 1);
	TrafficLight leftOutgoingTrafficLight(tcpConnection, 2);
	TrafficLight rightOutgoingTrafficLight(tcpConnection, 3);
	TrafficLight rightIngoingTrafficLight(tcpConnection, 4);
	WaterlevelDetection waterlevelDetection(tcpConnection);
	
	Door leftNormalDoor("Left", tcpConnection, false);
	Door rightNormalDoor("Right", tcpConnection, false);
	
	LockableDoor leftLockableDoor("Left", tcpConnection, true);
	LockableDoor rightLockableDoor("Right", tcpConnection, true);
			
	SluiceDoor leftSluiceDoor(leftOutgoingTrafficLight, leftIngoingTrafficLight, leftNormalDoor, leftBottomValve, leftMiddleValve, leftTopValve);
	SluiceDoor rightSluiceDoor(rightOutgoingTrafficLight, rightIngoingTrafficLight, rightNormalDoor, rightBottomValve, rightMiddleValve, rightTopValve);
	EventGenerator eventGenerator(leftNormalDoor, rightNormalDoor, waterlevelDetection);
	
	SluiceDoor leftLockableSluiceDoor(leftOutgoingTrafficLight, leftIngoingTrafficLight, leftLockableDoor, leftBottomValve, leftMiddleValve, leftTopValve);
	SluiceDoor rightLockableSluiceDoor(rightOutgoingTrafficLight, rightIngoingTrafficLight, rightLockableDoor, rightBottomValve, rightMiddleValve, rightTopValve);

	Sluice* sluice;
		
	switch(poort)
	{
		case 5555:
		{
			sluice = new Sluice(waterlevelDetection, eventGenerator, leftSluiceDoor, rightSluiceDoor);
			break;
		}
		case 5556:
		{
			sluice = new Sluice(waterlevelDetection, eventGenerator, leftSluiceDoor, rightSluiceDoor);
		}

			break;
		case 5557:
		{
			sluice = new Sluice(waterlevelDetection, eventGenerator, leftLockableSluiceDoor, rightLockableSluiceDoor);	
		}
			break;
		case 5558:
		{
			sluice = new Sluice(waterlevelDetection, eventGenerator, leftSluiceDoor, rightSluiceDoor);
		}
			break;
		default:
			std::cout << "Met dit poortnummer kan ik niet verbinden" << std::endl;
			break;
	};
	
	std::thread poller(&Sluice::Run, *sluice);
	poller.detach();	
	
	iUserActions& userAction = eventGenerator;
	
	bool quit = false;
	
	while(!quit)
	{
		ShowMenu();
		char choice = GetUserInput();
		
		switch (choice)
		{
            case '1':
                userAction.StartPressed();
                break;
            case '2':
                userAction.VrijgevenVoorUitvarenPressed();
                break;
            case '3':
                userAction.VrijgevenVoorInvarenPressed();
                break;
            case '4':
                userAction.AlarmPressed();
                break;
            case '5':
                userAction.HerstelPressed();
                break;	
            case 'q':
                quit = true;
                break;		
            default:
				std::cerr << "Don't know this choice : (" << choice << ")" << std::endl;
				break;
		}
	}
	
	tcpConnection.CloseSocket(sock_fd);
	
	delete sluice;
	sluice = NULL;
	
	return 0;
} 
