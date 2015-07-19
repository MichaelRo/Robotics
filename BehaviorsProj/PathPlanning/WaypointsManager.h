/*
 * WaypointsManager.h
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include "../Framework/Structs.h"
#include "../Framework/Map.h"

#include <list>

using namespace std;

class WaypointsManager {
private:
	Map * _map;
	list<Structs::Point> _wayPoints;
	list<Structs::Point>::iterator _wayPointsIterator;

	void markWaypoints(list<Structs::Point> route);

public:
	WaypointsManager();
	WaypointsManager(list<Structs::Point> route, Map * map);

	list<Structs::Point> getWaypoints(int waypointsType);

	static int getDirection(Structs::Point src, Structs::Point dest);
};

#endif
