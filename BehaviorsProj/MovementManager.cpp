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

/**
	Calculates the needed (non-relative) yaw to get from a ceirtain start point to a goal point

	@param startPoint - the start point
	@param goalPoint - the goal point
	@return - yaw in degrees
*/
float MovementManager::calculateNeededYaw(Structs::Point startPoint, Structs::Point goalPoint) {
	float yDeltaToPoint = abs(goalPoint.getY() - startPoint.getY());
	float distanceToPoint = startPoint.distanceBetweenPoints(goalPoint);

	return Helper::radiansToDegrees(abs(acos(yDeltaToPoint / distanceToPoint) - M_PI));
}

void MovementManager::start() {
	//++ before or after?
	for (list<Structs::Point>::iterator wayPointsIterator = _wayPoints.begin(); wayPointsIterator != _wayPoints.end(); wayPointsIterator++) {
		Structs::Point currentWayPoint = *wayPointsIterator.operator ->();
		float neededYaw = calculateNeededYaw(_robot->getPosition(), currentWayPoint);

		GoToPoint * goToPointBehavior;

		_robot->Read();

		while (_robot->getPosition().distanceBetweenPoints(currentWayPoint) > COMPROMISED_DISTANCE) {
			goToPointBehavior = new GoToPoint(_robot, _localizationManager, currentWayPoint, neededYaw);

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
