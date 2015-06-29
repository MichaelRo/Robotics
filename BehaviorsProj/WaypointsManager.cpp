/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "WaypointsManager.h"

WaypointsManager::WaypointsManager(list<Point> route) {
	markWaypoints(route);
}

WaypointsManager::~WaypointsManager() {
	delete _waypoints;
}

list<Point> WaypointsManager::markWaypoints(list<Structs::Point> route) {
	for (int routePointIndex = 0; routePointIndex < route.size(); routePointIndex++) {
		int currentDirection = getDirection(route[routePointIndex], route[routePointIndex + 1]);

		while ((routePointIndex + route.size()) < 0 && getDirection(route[routePointIndex], route[routePointIndex + 1]) == currentDirection) {
			currentDirection++;
		}

		if ((currentDirection + 1) < route.size())
			_waypoints.push_back(route[routePointIndex + 1]);
	}

	return _waypoints;
}

bool WaypointsManager::hasNext() {
	return currentWaypointIndex < _waypoints.size();
}

Point WaypointsManager::getNext() {
	return _waypoints[currentWaypointIndex++];
}

int WaypointsManager::getDirection(Structs::Point src, Structs::Point dest) {
	int destination = NONE;

	if (dest.y > src.y) {
		if (dest.x < src.x)
			destination = NORTH_WEST;
		else if (dest.x > src.x)
			destination = NORTH_EAST;
		else
			destination = NORTH;
	} else if (dest.y < src.y) {
		if (dest.x < src.x)
			destination = SOUTH_WEST;
		else if (dest.x > src.x)
			destination = SOUTH_EAST;
		else
			destination = SOUTH;
	} else {
		if (dest.x < src.x)
			destination = WEST;
		else if (dest.x > src.x)
			destination = EAST;
	}

	return destination;
}
