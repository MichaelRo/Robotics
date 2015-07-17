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
	_wayPoints = waypointsManager->getWaypoints(WaypointsManager::WAYPOINT_FOR_MAP);
}

void MovementManager::start() {
	for (list<Structs::Point>::iterator wayPointsIterator = _wayPoints.begin(); wayPointsIterator != _wayPoints.end(); wayPointsIterator++) {
		Structs::Point currentWayPoint = *wayPointsIterator.operator ->();

		if (_robot->getPosition().distanceBetweenPoints(currentWayPoint) > Helper::COMPROMISED_DISTANCE) {
			GoToPoint * goToPointBehavior;

			_robot->Read();

			while (_robot->getPosition().distanceBetweenPoints(currentWayPoint) > Helper::COMPROMISED_DISTANCE) {
				goToPointBehavior = new GoToPoint(_robot, _localizationManager, currentWayPoint);

				_robot->Read();

				if (goToPointBehavior->startCondition()) {
					while (!goToPointBehavior->stopCondition()) {
						goToPointBehavior->action();
					}
				}
			}
		}
	}
}
