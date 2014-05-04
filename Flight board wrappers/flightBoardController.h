//Author:	Michael Baxter <20503664@student.uwa.edu.au>
//Date:		25-4-2014
//Version:	v1.2
//
//Description:	Wrapper of servoblaster.  Use to make hex move.  Also use for gimble control.

#ifndef __FLIGHTBOARDCONTROLLER_H_INCLUDED__
#define __FLIGHTBOARDCONTROLLER_H_INCLUDED__

#include <cstdio>		//sprintf
#include <cstdlib>		//system

#define SERVOBLASTER_PATH "/home/pi/PiBits/ServoBlaster/user/servod"

#define AILERON_PIN 11
#define ELEVATOR_PIN 12
#define RUDDER_PIN 15
#define GIMBLE_PIN 16

#define PWM_NEUTRAL 150
#define PWM_LIMIT 40
#define SPEED_NEUTRAL 0
#define SPEED_LIMIT 100


class FlightBoardController {
public:

	FlightBoardController(void);
	
	int getAileron(void);
	int getElevator(void);
	int getRudder(void);
	int getGimble(void);
	
	void setAileron(int);
	void setElevator(int);
	void setRudder(int);
	void setGimble(int);
	
private:
	int aileron;
	int elevator;
	int rudder;
	int gimble;
	char servopos[128];
	
	int speed2PWM(int);
	int isSpeedValid(int);
	int makeSpeedValid(int);
};

#endif //__FLIGHTBOARDCONTROLLER_H_INCLUDED__
