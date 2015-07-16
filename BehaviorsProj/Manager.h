/*
 * Manager.h
 *
 *  Created on: June 29, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include <list>
#include <iostream>

#include "Robot.h"
#include "Map.h"
#include "PathPlanner.h"
#include "WaypointsManager.h"
#include "LocalizationManager.h"
#include "Structs.h"
#include "MovementManager.h"

using namespace std;

class Manager {
private:
	Robot * _robot;
	ConfigurationManager * _configurationManager;
	Map * _map;
	PathPlanner * _pathPlanner;
	WaypointsManager * _waypointsManager;
	LocalizationManager * _localizationManager;
	MovementManager * _movementManager;

public:
	Manager(ConfigurationManager * configurationManager, Robot * robot);
	virtual ~Manager();

	void run();
	Map * initializeMap();
	list<Structs::Point> getRoute();
};

#endif
