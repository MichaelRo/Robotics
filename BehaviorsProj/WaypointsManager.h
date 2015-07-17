/*
 * WaypointsManager.h
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include "Structs.h"
#include "Map.h"

#include <list>

using namespace std;

class WaypointsManager {
private:
	Map * _map;
	list<Structs::Point> _wayPoints;
	list<Structs::Point>::iterator _wayPointsIterator;

	void markWaypoints(list<Structs::Point> route);

public:
	enum Direction {NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST, NONE};
	enum WaypointType {WAYPOINT_FOR_MAP, WAYPOINT_FOR_GRID};

	WaypointsManager();
	WaypointsManager(list<Structs::Point> route, Map * map);

	list<Structs::Point> getWaypoints(int waypointsType);

	static int getDirection(Structs::Point src, Structs::Point dest);
};

#endif
