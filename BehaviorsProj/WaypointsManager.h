/*
 * WaypointsManager.h
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include "Structs.h"

#include <list>

using namespace std;

class WaypointsManager {
private:
	list<Structs::Point> _wayPoints;
	list<Structs::Point>::iterator _wayPointsIterator;

	void markWaypoints(list<Structs::Point> route);

public:
	static const int NORTH_WEST = 1;
	static const int NORTH = 2;
	static const int NORTH_EAST = 3;
	static const int EAST = 4;
	static const int SOUTH_EAST= 5;
	static const int SOUTH = 6;
	static const int SOUTH_WEST = 7;
	static const int WEST = 8;
	static const int NONE = 9;

	WaypointsManager();
	WaypointsManager(list<Structs::Point> route);

	list<Structs::Point> getWaypoints();
	bool hasNext();
	Structs::Point getNext();

	static int getDirection(Structs::Point src, Structs::Point dest);
};

#endif
