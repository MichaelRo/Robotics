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

#include "SearchCell.h"
#include <vector>

using namespace std;

class PathPlanner {

public:
	PathPlanner(void);
	virtual ~PathPlanner(void);

	void findPath(Point currentPos, Point targetPos);
	Point nextPathPos();

	void clearOpenList() {
		_openList.clear();
	}

	void clearVisitedList() {
			_visitedList.clear();
	}

	void clearPathToGoal() {
			_openList.clear();
	}

	bool _initializedStartGoal;
	bool _foundGoal;

private :
	void setStartAndGoal(SearchCell start, SearchCell goal);
	void pathOpened(int x, int y, float newCost, SearchCell* parent);
	SearchCell* getNextCell();
	void continuePath();

	SearchCell* _startCell;
	SearchCell* _goalCell;
	std::vector<SearchCell*> _openList;
	std::vector<SearchCell*> _visitedList;
	std::vector<Point*> _pathToGoal;
};

#endif /* PATHPLANNER_H_ */
