//Basic function that causes the Hexacopter to continuously read its GPS position and compare it to its start location
//Written by Omid Targhagh, based on work done by Michael Baxter

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <math.h> 

#include <gps_qstarz.h>
#include "logger.h"
#include "lawnmower_control.h"	//Really only need distance function

using namespace std;

bool curses_started = false;
int TITLE_HEIGHT = 4;

void endCurses(void);
void startCurses(void);

int main() {

	GPS gps = GPS();		//Initialises GPS
	if(gps.setup() != GPS_OK) {
		cout << "Error setting up gps (check that it has been switched on). Terminating program." << endl;
		return -1;
	}
	gps.start();

	Logger distLog = Logger("Distance.txt");
	GPS_Data data;
	Pos start, current;
	bool started = false;
	while(!started) {
		(&gps)->getGPS_Data(&data);
		start.lat = (data.latitude);
		start.lon = (data.longitude);
		cout << start.lat << " " << start.lon << endl;
		if ((abs((int)(start.lat) - (-31)) < 1) && (abs((int)(start.lon) - (115)) < 1)) {
			started = true;
		}
		usleep(500000);
	}
	double startTime = data.time;
	usleep(1000000);

	initscr();	//Set up curses
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	refresh();
	int LINES, COLUMNS;
	getmaxyx(stdscr, LINES, COLUMNS);

	WINDOW *title_window = newwin(TITLE_HEIGHT, COLUMNS -1, 0, 0);
	wattron(title_window, COLOR_PAIR(1));
	wborder(title_window, ' ' , ' ' , '-', '-' , '-', '-', '-', '-');
	wmove(title_window, 1, 0);
	wprintw(title_window, "\t%s\t\n", "DISTANCE");
	wprintw(title_window, "\t%s\t\n", "Hexacopter continuously measures the distance from where it started.");
	wrefresh(title_window);
	
	WINDOW *msg_window = newwin(LINES - TITLE_HEIGHT -1, COLUMNS -1, TITLE_HEIGHT, 0);
	wattron(msg_window, COLOR_PAIR(2));
	
	double distance;
	char str[BUFSIZ];
	while(true) {
		(&gps)->getGPS_Data(&data);
		current.lat = (data.latitude);
		current.lon = (data.longitude);

		distance = calculate_distance(start, current);
		sprintf(str, "%f %f", (data.time)-startTime, distance);
		distLog.writeLogLine(str, false);

		wclear(msg_window);
		wprintw(msg_window, "\n");
		wprintw(msg_window, "Started at \t%f\t%f\n", start.lat, start.lon);
		wprintw(msg_window, "Currently at \t%f\t%f\n", current.lat, current.lon);
		wprintw(msg_window, "\n");
		wprintw(msg_window, "Distance:\t\t%d m\n", distance);
		wprintw(msg_window, "Time Difference:\t%f seconds\n", (data.time)-startTime);
		wprintw(msg_window, "\n");
		wrefresh(msg_window);
		usleep(100000);
	}
	return 0;
}
