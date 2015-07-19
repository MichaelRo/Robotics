/*
 * main.cpp
 *
 *  Created on: June 13, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */
#include "Control/Robot.h"
#include "Utils/ConfigurationManager.h"
#include "Framework/Map.h"
#include "PathPlanning/PathPlanner.h"
#include "PathPlanning/WaypointsManager.h"
#include "Control/Manager.h"

int main (int argc, const char * argv[]) {
//	Robot igal("10.10.245.65",6665);
	Robot igal("localhost",6665);
	Manager* manager = new Manager(&igal);
	manager->run();
}
