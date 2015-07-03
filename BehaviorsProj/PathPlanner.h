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

#include <iostream>
#include <iomanip>
#include <cmath>
#include <tuple>
#include <vector>
#include <list>
#include <algorithm>
#include <limits>

using namespace std;

class PathPlanner {
private:
	static const int GRADE_FACTOR = 1;

	list<Structs::Node> _openList;
	list<Structs::Node> _closedList;
	Structs::Point * _startPoint;
	Structs::Point * _endPoint;
	Map * _map;

	list<Structs::Node> getNeighbors(Structs::Node * node);
	list<Structs::Point> reconstruct_path(Structs::Node endNode);
	bool listContains(list<Structs::Node> list, Structs::Node nodeToLookFor);

public:
	PathPlanner(Map * map, Structs::Point * startPoint, Structs::Point * endPoint);
	virtual ~PathPlanner(void);

	list<Structs::Point> performAStar();
	Structs::Node extractMinNode(list<Structs::Node> * list);
};

#endif
