/*
 * MovementManager.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "MovementManager.h"

MovementManager::~MovementManager() {
	delete _robot;
	delete _waypointsManager;
	delete _localizationManager;
}

MovementManager::MovementManager(Robot * robot, WaypointsManager * waypointsManager, LocalizationManager * localizationManager) {
	_robot = robot;
	_waypointsManager = waypointsManager;
	_localizationManager = localizationManager;
}

float MovementManager::calculateWantedYaw(Structs::Point startPoint, Structs::Point goalPoint) {
	return acosf((goalPoint._x - startPoint._x) * startPoint.distanceBetweenPoints(goalPoint));
}

Structs::Point MovementManager::getCurrentWaypoint() {
	return _waypointsManager->hasNext() ? _waypointsManager->getNext() : NULL;
}

void MovementManager::start() {
	Structs::Point currentWayPoint;
	float wantedYaw = calculateWantedYaw(_robot->getLocation().pointValue(), currentWayPoint);

	while ((currentWayPoint = getCurrentWaypoint()) != NULL) {
		GoToPoint * goToPointBehavior;

		while (_robot->getLocation().pointValue().distanceBetweenPoints(currentWayPoint) > COMPROMISED_DISTANCE) {
			goToPointBehavior = new GoToPoint(_robot, currentWayPoint, wantedYaw);

			if (goToPointBehavior->startCondition()) {
				while (!goToPointBehavior->stopCondition()) {
					goToPointBehavior->action();

					_localizationManager->updateParticles(Location(currentWayPoint, wantedYaw), _robot->getLaserScan());
					_robot->setRobotLocation(_localizationManager->getProbableLocation());
				}
			}
		}
	}
}
