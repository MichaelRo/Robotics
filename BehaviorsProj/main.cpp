/*
 * main.cpp
 *
 *  Created on: June 13, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */
#include "Robot.h"
#include "ConfigurationManager.h"
#include "Map.h"
#include "PathPlanner.h"
#include "WaypointsManager.h"
#include "Manager.h"

int main (int argc, const char * argv[]) {
//	Robot igal("10.10.245.65",6665);
	Robot igal("localhost",6665);
	Manager* manager = new Manager(&igal);
	manager->run();
}
