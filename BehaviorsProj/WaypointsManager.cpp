/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "WaypointsManager.h"

WaypointsManager::WaypointsManager(list<Structs::Point> route) {
	markWaypoints(route);
}

list<Structs::Point> WaypointsManager::markWaypoints(list<Structs::Point> route) {
	list<Structs::Point>::iterator routePointsIterator = route.begin();
	int continuingDirection = getDirection(routePointsIterator.operator ->(), (++routePointsIterator).operator ->());

	while (routePointsIterator != route.end()) {
		int currentDirection = getDirection(routePointsIterator.operator ->(), (++routePointsIterator).operator ->());

		if (currentDirection != continuingDirection) {
			continuingDirection = currentDirection;

			_wayPoints.push_back(routePointsIterator.operator ->());
		}
	}

	_wayPointsIterator = _wayPoints.begin();

	return _wayPoints;
}

bool WaypointsManager::hasNext() {
	return _wayPointsIterator != _wayPoints.end();
}

Structs::Point WaypointsManager::getNext() {
	return (++_wayPointsIterator).operator ->();
}

int WaypointsManager::getDirection(Structs::Point src, Structs::Point dest) {
	int destination = NONE;

	if (dest._y > src._y) {
		if (dest._x < src._x)
			destination = NORTH_WEST;
		else if (dest._x > src._x)
			destination = NORTH_EAST;
		else
			destination = NORTH;
	} else if (dest._y < src._y) {
		if (dest._x < src._x)
			destination = SOUTH_WEST;
		else if (dest._x > src._x)
			destination = SOUTH_EAST;
		else
			destination = SOUTH;
	} else {
		if (dest._x < src._x)
			destination = WEST;
		else if (dest._x > src._x)
			destination = EAST;
	}

	return destination;
}
