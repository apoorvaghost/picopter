//Author:	Michael Baxter 	20503664@student.uwa.edu.au
//Date:		2-9-2014
//Version:	v1.0
//
//Desciption:	Class used for piksi gps.  This is just so I can say i've got it working.
//
//				BE SURE TO CREATE RAM-DEV BEFOREHAND


#ifndef __GPS_PIKSI_H_INCLUDED__
#define __GPS_PIKSI_H_INCLUDED__

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "logger.h"

#define PIKSI_FILE "piksi_data.txt"
#define PIKSI_SCRIPT "piksi_data.txt"


#define PGPS_OK 0


typedef struct {
	double time;
	double longitude;
	double latitude;
	int numSatelites;
	double horizAccuracy;
} GPS_Data;


class GPS {
public:
	GPS(void);
	GPS(const GPS&);
	virtual ~GPS(void);
	
	int setup(void);
	int start(void);
	int stop(void);
	int close(void);
	
	int getGPS_Data(PGPS_Data*);
private:
	bool ready;
	bool running;
	Logger* log;
	
	ifstream* dataFile;
};

#endif// __GPS_PIKSI_INCLUDED__

