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

list<Structs::Point> MovementManager::initializeWaypoints(list<Structs::Point> mapWayPoints) {
	list<Structs::Point> realLifeWayPoints = list<Structs::Point>(mapWayPoints.size());

	for (list<Structs::Point>::iterator mapWayPointsIterator = mapWayPoints.begin(); mapWayPointsIterator != mapWayPoints.end(); mapWayPointsIterator++) {
		// Multiply in map resolution
		realLifeWayPoints.push_back(*(mapWayPointsIterator.operator ->()) * 2.5);
	}

	return realLifeWayPoints;
}

float MovementManager::calculateWantedYaw(Structs::Point startPoint, Structs::Point goalPoint) {
	return abs(acos(abs(goalPoint._y - startPoint._y) / startPoint.distanceBetweenPoints(goalPoint)) - M_PI) + _robot->getLocation()._yaw;
}

void MovementManager::start() {
	//++ before or after?
	for (list<Structs::Point>::iterator wayPointsIterator = _wayPoints.begin(); wayPointsIterator != _wayPoints.end(); wayPointsIterator++) {
		Structs::Point * currentWayPoint = wayPointsIterator.operator ->();
		float wantedYaw = calculateWantedYaw(_robot->getLocation().pointValue(), currentWayPoint->realPointToRobotPoint());

		GoToPoint * goToPointBehavior;

		_robot->Read();

		while (_robot->getLocation().pointValue().distanceBetweenPoints(currentWayPoint->realPointToRobotPoint()) > COMPROMISED_DISTANCE) {
			goToPointBehavior = new GoToPoint(_robot, _localizationManager, currentWayPoint->realPointToRobotPoint(), wantedYaw);

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
