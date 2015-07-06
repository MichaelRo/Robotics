/*
 * MovementManager.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "MovementManager.h"

MovementManager::~MovementManager() {
	delete _robot;
	delete _localizationManager;
}

MovementManager::MovementManager(Robot * robot, LocalizationManager * localizationManager, list<Structs::Point> wayPoints) {
	_robot = robot;
	_localizationManager = localizationManager;
	_wayPoints = wayPoints;
}

float MovementManager::calculateWantedYaw(Structs::Point startPoint, Structs::Point goalPoint) {
	return acosf((goalPoint._x - startPoint._x) * startPoint.distanceBetweenPoints(goalPoint));
}

void MovementManager::start() {
	//++ before or after?
	for (list<Structs::Point>::iterator wayPointsIterator = _wayPoints.begin(); wayPointsIterator != _wayPoints.end(); wayPointsIterator++) {
		Structs::Point * currentWayPoint = wayPointsIterator.operator ->();
		float wantedYaw = calculateWantedYaw(_robot->getLocation().pointValue(), *currentWayPoint);

		GoToPoint * goToPointBehavior;

		while (_robot->getLocation().pointValue().distanceBetweenPoints(*currentWayPoint) > COMPROMISED_DISTANCE) {
			goToPointBehavior = new GoToPoint(_robot, *currentWayPoint, wantedYaw);

			if (goToPointBehavior->startCondition()) {
				while (!goToPointBehavior->stopCondition()) {
					goToPointBehavior->action();

					Structs::Location wantedLocation(*currentWayPoint, wantedYaw);
					_localizationManager->updateParticles(wantedLocation, _robot->getLaserScan());
					_robot->setRobotLocation(_localizationManager->getProbableLocation());
				}
			}
		}
	}
}
