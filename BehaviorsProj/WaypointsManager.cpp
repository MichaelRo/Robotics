/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "WaypointsManager.h"

/**
	Initializes the WaypointsManager and marks the waypoints that the robot should go through with a given route.

	@param route - Route of points, represented as list<Structs::Point>
*/
WaypointsManager::WaypointsManager(list<Structs::Point> route) {
	markWaypoints(route);

	// Initializes the waypoints iterator
	_wayPointsIterator = _wayPoints.begin();
}

/**
	Marks waypoints that the robot should go through with a given route.

	@param route - Route of points, represented as list<Structs::Point>
*/
void WaypointsManager::markWaypoints(list<Structs::Point> route) {
	list<Structs::Point>::iterator routePointsIterator = route.begin();
	int continuingDirection = getDirection(routePointsIterator.operator ->(), (++routePointsIterator).operator ->());

	// Goes through all the points in the route and checks its direction
	while (routePointsIterator != route.end()) {
		int currentDirection = getDirection(routePointsIterator.operator ->(), (++routePointsIterator).operator ->());

		// If the direction from one point to another has changed, this point should be marked as a waypoint
		if (currentDirection != continuingDirection) {
			continuingDirection = currentDirection;

			_wayPoints.push_back(routePointsIterator.operator ->());
		}
	}
}

/**
	Gets the waypoints that have been marked within the route that was given to the constructor

	@return - Waypoints, represented as list<Structs::Point>
*/
list<Structs::Point> WaypointsManager::getWaypoints() {
	return _wayPoints;
}

/**
	Uses the waypoints Iterator to check whether there is more waypoins or not

	@return - a boolean indicates whether there is more waypoints
*/
bool WaypointsManager::hasNext() {
	return _wayPointsIterator != _wayPoints.end();
}

/**
	Uses the waypoints Iterator to get the next waypoint

	@return - the next waypoint
*/
Structs::Point WaypointsManager::getNext() {
	return (++_wayPointsIterator).operator ->();
}

/**
	Checks what is the direction from a given point to another

	@param src - the source point
	@param dest - the destination point
	@return - the direction, represented by an int directions enum
*/
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
