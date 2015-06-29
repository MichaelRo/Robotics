/*
 * Manager.cpp
 *
 *  Created on: June 29, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Manager.h"

Manager::Manager(ConfigurationManager* configurationManager, Robot* robot) {
	_robot = robot;
	_configurationManager = configurationManager;
}

void Manager::run() {
	initializeMap();
	padMap();

	getRoute();
	getWayPoints();

	runRobot();
}

Manager::~Manager() {
	delete _robot;
	delete _configurationManager;
	delete _map;
	delete _pathPlanner;
	delete _waypointsManager;
	delete _localizationManager;
}
