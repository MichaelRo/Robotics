/*
 * PathPlanner.h
 *
 *  Created on: Jun 16, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include "Map.h"
#include "Structs.h"
#include "AStarPriority.h"

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
	list<Structs::Node> _openList;
	std::priority_queue<Structs::Node,vector<Structs::Node>,AStarPriority> _openQueue;
	list<Structs::Node> _closedList;
	Structs::Point * _startPoint;
	Structs::Point * _endPoint;
	Map * _map;

	list<Structs::Node> getNeighbors(Structs::Node *node);
	list<Structs::Point> reconstruct_path(Structs::Node endNode);
	bool listContains(list<Structs::Node> list, Structs::Node nodeToLookFor);

public:
	PathPlanner(Map * map, Structs::Point * startPoint, Structs::Point * endPoint);
	virtual ~PathPlanner(void);

	list<Structs::Point> performAStar();
	Structs::Node extractMinNode(list<Structs::Node> * list);
};

#endif
