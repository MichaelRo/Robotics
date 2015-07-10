/*
 * MovementManager.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "MovementManager.h"

MovementManager::~MovementManager() {

}

MovementManager::MovementManager(Robot * robot, LocalizationManager * localizationManager, list<Structs::Point> wayPoints) {
	_robot = robot;
	_localizationManager = localizationManager;
	// Check if the waypoints are really different than the points that the robot returns (the player)
	_wayPoints = wayPoints;
//	_wayPoints = initializeWaypoints(wayPoints);
}

float MovementManager::calculateWantedYaw(Structs::Point startPoint, Structs::Point goalPoint) {
	float yaw = abs(acos(abs(goalPoint._y - startPoint._y) / startPoint.distanceBetweenPoints(goalPoint)) - M_PI) + _robot->getLocation().realLocationToRobotLocation()._yaw;

	if (yaw >= M_PI)
		yaw -= 2*M_PI;
	return yaw;
}

void MovementManager::start() {
	//++ before or after?
	for (list<Structs::Point>::iterator wayPointsIterator = _wayPoints.begin(); wayPointsIterator != _wayPoints.end(); wayPointsIterator++) {
		Structs::Point * currentWayPoint = wayPointsIterator.operator ->();
		float wantedYaw = calculateWantedYaw(_robot->getLocation().pointValue().realPointToRobotPoint(), *currentWayPoint);

		GoToPoint * goToPointBehavior;

		_robot->Read();

		while (_robot->getLocation().pointValue().realPointToRobotPoint().distanceBetweenPoints(*currentWayPoint) > COMPROMISED_DISTANCE) {
			goToPointBehavior = new GoToPoint(_robot, _localizationManager, *currentWayPoint, wantedYaw);

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
