/*
 * MovementManager.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "MovementManager.h"

MovementManager::~MovementManager() {
	delete _waypointsManager;
}

MovementManager::MovementManager(WaypointsManager * waypointsManager) {
	_waypointsManager = waypointsManager;
}

Structs::Point MovementManager::getCurrentWaypoint() {
	return _waypointsManager->hasNext() ? _waypointsManager->getNext() : NULL;
}

void MovementManager::start() {
	Structs::Point currentWayPoint;

	while ((currentWayPoint = getCurrentWaypoint()) != NULL) {
		GoToPoint goToPointBehavior();
	}
}
