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
#include <math.h>

#include "Structs.h"
#include <vector>
#include <list>

using namespace std;

class PathPlanner {

public:
	list<Structs::SearchCell> _openList;
	list<Structs::SearchCell> _closedList;
	Map *_map;

	PathPlanner(void);
	virtual ~PathPlanner(void);

	void findPath(Structs::Point currentPos, Structs::Point targetPos);
	list<Structs::Point> performAStar(Map *map ,Structs::Point *startPoint, Structs::Point *endPoint);
	Structs::SearchCell* extractMinNode(list<Structs::SearchCell> list);

	void clearOpenList() {
		_openList.clear();
	}

	void clearPathToGoal() {
		_openList.clear();
	}
private :
	void setStartAndGoal(Structs::SearchCell start, Structs::SearchCell goal);
	//void pathOpened(int x, int y, float newCost, Structs::SearchCell* parent);
	Structs::SearchCell* getNextCell();
	void continuePath();

	Structs::SearchCell* _startCell;
	Structs::SearchCell* _goalCell;
	std::vector<Structs::Point*> _pathToGoal;
};

#endif
