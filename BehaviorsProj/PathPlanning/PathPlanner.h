/*
 * PathPlanner.h
 *
 *  Created on: Jun 16, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include "AStarPriority.h"
#include "WaypointsManager.h"
#include "../Framework/Map.h"
#include "../Framework/Structs.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <tuple>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

class PathPlanner {
private:
	const int COST_BETWEEN_NODES = 1;

	std::priority_queue<Structs::Node, vector<Structs::Node>, AStarPriority> _openQueue;
	Structs::Point _startPoint;
	Structs::Point _endPoint;
	Map * _map;
	map<int, Structs::Point> _parentsMap;

	list<Structs::Node> getNeighbors(Structs::Node * node);
	list<Structs::Point> reconstruct_path(Structs::Point endPoint);
	double calcDirectionFactor(Structs::Point p1, Structs::Point p2, Structs::Point p3);
	double calcWallFactor(Structs::Point point, int wallDis);

public:
	PathPlanner(Map * map, Structs::Point startPoint, Structs::Point endPoint);
	virtual ~PathPlanner(void);

	list<Structs::Point> performAStar();
};

#endif
