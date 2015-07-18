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
WaypointsManager::WaypointsManager(list<Structs::Point> route, Map * map) {
	_map = map;

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
	Structs::Point * sourcePoint = routePointsIterator.operator ->();
	std::advance(routePointsIterator, 1);
	Structs::Point * destinationPoint = routePointsIterator.operator ->();

	int continuingDirection = getDirection(*sourcePoint, *destinationPoint);

	// Goes through all the points in the route and checks its direction
	while (routePointsIterator != route.end()) {
		sourcePoint = routePointsIterator.operator ->();
		std::advance(routePointsIterator, 1);
		destinationPoint = routePointsIterator.operator ->();

		int currentDirection = getDirection(*sourcePoint, *destinationPoint);

		// If the direction from one point to another has changed, this point should be marked as a waypoint
		if (currentDirection != continuingDirection) {
			continuingDirection = currentDirection;

			_wayPoints.push_back(*sourcePoint);
		}
	}
}

/**
	Gets the waypoints that have been marked within the route that was given to the constructor

	@param resolution - the wanted resolution
	@return - Waypoints, represented as list<Structs::Point>
*/
list<Structs::Point> WaypointsManager::getWaypoints(int waypointsType) {
	list<Structs::Point> wayPoints = list<Structs::Point>();

	int index = 1;

	for (list<Structs::Point>::iterator wayPointsIterator = _wayPoints.begin(); wayPointsIterator != _wayPoints.end(); wayPointsIterator++) {
		Structs::Point waypoint;

		// VERY HORANI!
		if (index != 1 && index != 2 && index != 4 && index != 5) {
			switch (waypointsType) {
				case WaypointType::WAYPOINT_FOR_MAP:
					waypoint = (*wayPointsIterator.operator ->()) * (ceil(_map->getGridResolution() / _map->getMapResolution()) / 2);

					break;
				case WaypointType::WAYPOINT_FOR_GRID:
					waypoint = *wayPointsIterator.operator ->();

					break;
				default:
					break;
			}

			wayPoints.push_back(waypoint);
		}

		index++;
	}

	return wayPoints;
}

/**
	Checks what is the direction from a given point to another

	@param src - the source point
	@param dest - the destination point
	@return - the direction, represented by an int directions enum
*/
int WaypointsManager::getDirection(Structs::Point src, Structs::Point dest) {
	int direction = Direction::NONE;

	if (dest.getY() > src.getY()) {
		if (dest.getX() < src.getX())
			direction = Direction::NORTH_WEST;
		else if (dest.getX() > src.getX())
			direction = Direction::NORTH_EAST;
		else
			direction = Direction::NORTH;
	} else if (dest.getY() < src.getY()) {
		if (dest.getX() < src.getX())
			direction = Direction::SOUTH_WEST;
		else if (dest.getX() > src.getX())
			direction = Direction::SOUTH_EAST;
		else
			direction = Direction::SOUTH;
	} else {
		if (dest.getX() < src.getX())
			direction = Direction::WEST;
		else if (dest.getX() > src.getX())
			direction = Direction::EAST;
	}

	return direction;
}
