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
#include "WaypointsManager.h"
#include "behaviors/GoToPoint.h"

using namespace std;

class MovementManager {
private:
	WaypointsManager * _waypointsManager;

	Structs::Point getCurrentWaypoint();

public:
	MovementManager(WaypointsManager * waypointsManager);
	virtual ~MovementManager();

	void start();
};

#endif
