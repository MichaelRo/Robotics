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

#include "MovementManager.h"
#include "Robot.h"
#include "../Framework/Map.h"
#include "../PathPlanning/PathPlanner.h"
#include "../PathPlanning/WaypointsManager.h"
#include "../Localization/LocalizationManager.h"
#include "../Framework/Structs.h"

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
	Manager(Robot * robot);
	virtual ~Manager();

	void run();
	Map * initializeMap();
	list<Structs::Point> getRoute();
};

#endif
