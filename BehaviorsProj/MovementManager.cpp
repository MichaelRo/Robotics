/*
 * MovementManager.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "MovementManager.h"

MovementManager::~MovementManager() {

}

MovementManager::MovementManager(Robot * robot, LocalizationManager * localizationManager, WaypointsManager * waypointsManager) {
	_robot = robot;
	_localizationManager = localizationManager;
	_wayPoints = waypointsManager->getWaypoints(WaypointsManager::WAYPOINT_FOR_ROBOT);
}

float MovementManager::calculateWantedYaw(Structs::Point startPoint, Structs::Point goalPoint) {
	return abs(acos(abs(goalPoint.getY() - startPoint.getY()) / startPoint.distanceBetweenPoints(goalPoint)) - M_PI);
}

void MovementManager::start() {
	//++ before or after?
	for (list<Structs::Point>::iterator wayPointsIterator = _wayPoints.begin(); wayPointsIterator != _wayPoints.end(); wayPointsIterator++) {
		Structs::Point currentWayPoint = *wayPointsIterator.operator ->();
		float wantedYaw = calculateWantedYaw(_robot->getPosition(), currentWayPoint);

		GoToPoint * goToPointBehavior;

		_robot->Read();

		while (_robot->getPosition().distanceBetweenPoints(currentWayPoint) > COMPROMISED_DISTANCE) {
			goToPointBehavior = new GoToPoint(_robot, _localizationManager, currentWayPoint, wantedYaw);

			_robot->Read();

			if (goToPointBehavior->startCondition()) {
				while (!goToPointBehavior->stopCondition()) {
					goToPointBehavior->action();
				}
			}
		}

		// Maybe (delete goToPointBehavior;) ?
	}
}
