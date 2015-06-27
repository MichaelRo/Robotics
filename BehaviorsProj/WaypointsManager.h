/*
 * WaypointsManager.h
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <SearchCell.h>

class WaypointsManager {
private:
	vector<Point> _waypoints;
	int currentWaypointIndex;

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
	WaypointsManager(vector<Point> route);
	virtual ~WaypointsManager();

	void markWaypoints(vector<Point> route);
	bool hasNext();
	Point getNext();

	static int getDirection(Point src, Point dest);
};

#endif /* WAYPOINTSMANAGER_H_ */
