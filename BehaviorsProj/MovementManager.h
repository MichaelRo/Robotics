/*
 * MovementManager.h
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef MOVEMENTMANAGER_H_
#define MOVEMENTMANAGER_H_

#include <list>

#include "Structs.h"
#include "Robot.h"
#include "WaypointsManager.h"
#include "LocalizationManager.h"
#include "behaviors/GoToPoint.h"

using namespace std;

class MovementManager {
private:
	static const int COMPROMISED_DISTANCE = 0.2;

	Robot * _robot;
	WaypointsManager * _waypointsManager;
	LocalizationManager * _localizationManager;

	float calculateWantedYaw(Structs::Point startPoint, Structs::Point goalPoint);
	Structs::Point getCurrentWaypoint();

public:
	MovementManager(Robot * robot, WaypointsManager * waypointsManager, LocalizationManager * localizationManager);
	virtual ~MovementManager();

	void start();
};

#endif
