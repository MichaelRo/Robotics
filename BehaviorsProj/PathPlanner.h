/*
 * PathPlanner.h
 *
 *  Created on: Jun 16, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include "Map.h"

#include <iostream>
#include <iomanip>
#include <cmath>

#include "Structs.h"
#include <tuple>
#include <vector>
#include <list>

using namespace std;

class PathPlanner {
private:
	list<Structs::Node> _openList;
	list<Structs::Node> _closedList;

	Structs::Node * _startNode;

	static const int GRADE_FACTOR = 1;

	void pathOpened(int x, int y, float newCost, Structs::Node* parent);
	void continuePath();
	list<Structs::Node> getNeighbors(Structs::Node *node, Map *map);
	list<Structs::Point> reconstruct_path(Structs::Node endNode);

public:
	PathPlanner(void);
	virtual ~PathPlanner(void);

	list<Structs::Point> performAStar(Map *map ,Structs::Point *startPoint, Structs::Point *endPoint);
	Structs::Node extractMinNode(list<Structs::Node> list);
	void clearOpenList();
	void clearPathToGoal();
};

#endif
