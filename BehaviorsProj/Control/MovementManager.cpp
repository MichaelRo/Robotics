/*
 * MovementManager.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "MovementManager.h"

/**
	Destructs MovementManager.
*/
MovementManager::~MovementManager() {

}

/**
	Initializes the MovementManager.

	@param robot - the robot object to connect with him (get information and give commands).
	@param localizationManager - the object that help to know the real location of the robot by particles.
	@param waypointsManager - the object that manage the calculation the path from the start point to the end point.
*/
MovementManager::MovementManager(Robot * robot, LocalizationManager * localizationManager, WaypointsManager * waypointsManager) {
	_robot = robot;
	_localizationManager = localizationManager;
	_wayPoints = waypointsManager->getWaypoints(Globals::WaypointType::WAYPOINT_FOR_MAP);
}

/**
  	This method tell the robot where to go by the waypoints.
 */
void MovementManager::start() {
	for (list<Structs::Point>::iterator wayPointsIterator = _wayPoints.begin(); wayPointsIterator != _wayPoints.end(); wayPointsIterator++) {
		Structs::Point currentWayPoint = *wayPointsIterator.operator ->();
		GoToPoint * goToPointBehavior;

		_robot->Read();

		while (_robot->getPosition().distanceBetweenPoints(currentWayPoint) > Globals::COMPROMISED_DISTANCE) {
			goToPointBehavior = new GoToPoint(_robot, _localizationManager, currentWayPoint);

			_robot->Read();

			if (goToPointBehavior->startCondition()) {
				while (!goToPointBehavior->stopCondition()) {
					goToPointBehavior->action();
				}
			}
		}
	}

	cout << "Igal: Mission Accomplished, now I have time to save the world from the missile of the Iranian gay community." << endl;
}
