/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "PathPlanner.h"
#include "Map.h"

#include <iostream>
#include <iomanip>
#include <math.h>

PathPlanner::PathPlanner(void) {
	this->_initializedStartGoal = false;
	this->_foundGoal = false;
}

PathPlanner::~PathPlanner(void) {

}

void PathPlanner::findPath(Point currentPos, Point targetPos) {
	if (!this->_initializedStartGoal) {
		for (unsigned int i = 0; i < this->_openList.size(); i++) {
			delete this->_openList[i];
		}
		this->_openList.clear();

		for (unsigned int i = 0; i < this->_visitedList.size(); i++) {
			delete this->_visitedList[i];
		}
		this->_visitedList.clear();

		for (unsigned int i = 0; i < this->_pathToGoal.size(); i++) {
			delete this->_pathToGoal[i];
		}
		this->_pathToGoal.clear();

		// Initialize start
		SearchCell start;
		start._xCoord = currentPos.x;
		start._yCoord = currentPos.y;

		// Initialize goal
		SearchCell goal;
		goal._xCoord = targetPos.x;
		goal._yCoord = targetPos.y;

		setStartAndGoal(start, goal);
		this->_initializedStartGoal = true;
	}

	if (this->_initializedStartGoal) {
		continuePath();
	}
}

void PathPlanner::setStartAndGoal(SearchCell start, SearchCell goal) {
	this->_startCell = new SearchCell(start._xCoord, start._yCoord, NULL);
	this->_goalCell = new SearchCell(goal._xCoord, goal._yCoord, &goal);

	this->_startCell->_G = 0;
	this->_startCell->_H = this->_startCell->ManhattanDistance(this->_goalCell);
	this->_startCell->_parent = 0;

	this->_openList.push_back(this->_startCell);
}

SearchCell* PathPlanner::getNextCell() {
	float bestF = 999999999.0f;
	int cellIndex = -1;
	SearchCell* nextCell = NULL;

	for(unsigned int i=0; i < this->_openList.size(); i++) {
		if (this->_openList[i]->getF() < bestF) {
			bestF = this->_openList[i]->getF();
			cellIndex = i;
		}
	}

	if (cellIndex >= 0) {
		nextCell = this->_openList[cellIndex];
		this->_visitedList.push_back(nextCell);
		this->_openList.erase(this->_openList.begin() + cellIndex);
	}

	return nextCell;
}

void PathPlanner::pathOpened(int x, int y, float newCost, SearchCell* parent) {
	int id = x * Map::MAP_COLUMNS + y;

	for (unsigned int i = 0; i < this->_visitedList.size(); i++) {
		if (id == this->_visitedList[i]->_id) {
			return;
		}
	}

	SearchCell* newChild = new SearchCell(x, y, parent);
	newChild->_G = newCost;
	newChild->_H = parent->ManhattanDistance(this->_goalCell);

	for (unsigned int i = 0; i < this->_openList.size(); i++) {
		if (id == this->_openList[i]->_id) {
			float newF = newChild->_G + newCost + this->_openList[i]->_H;

			if (this->_openList[i]->getF() > newF) {
				this->_openList[i]->_G = newChild->_G + newCost;
				this->_openList[i]->_parent = newChild;
			} else { // if the F is not better
				delete newChild;
				return;
			}
		}
	}

	this->_openList.push_back(newChild);
}

void PathPlanner::continuePath() {
	if (!this->_openList.empty()) {
		SearchCell* currentCell = getNextCell();

		if (currentCell->_id == this->_goalCell->_id) {
			this->_goalCell->_parent = currentCell->_parent;

			SearchCell* getPath;

			for (getPath = this->_goalCell; getPath != NULL; getPath = getPath->_parent) {
				this->_pathToGoal.push_back(new Point(getPath->_xCoord, getPath->_yCoord));
			}

			this->_foundGoal = true;
			return;
		} else {
			// right
			pathOpened(currentCell->_xCoord + 1, currentCell->_yCoord, currentCell->_G + 1, currentCell);
			// left
			pathOpened(currentCell->_xCoord - 1, currentCell->_yCoord, currentCell->_G + 1, currentCell);
			// up
			pathOpened(currentCell->_xCoord, currentCell->_yCoord + 1, currentCell->_G + 1, currentCell);
			// down
			pathOpened(currentCell->_xCoord, currentCell->_yCoord - 1, currentCell->_G + 1, currentCell);
			// left-up
			pathOpened(currentCell->_xCoord - 1, currentCell->_yCoord + 1, currentCell->_G + 1.414, currentCell);
			// right-up
			pathOpened(currentCell->_xCoord + 1, currentCell->_yCoord + 1, currentCell->_G + 1.414, currentCell);
			// left-down
			pathOpened(currentCell->_xCoord - 1, currentCell->_yCoord - 1, currentCell->_G + 1.414, currentCell);
			// right-down
			pathOpened(currentCell->_xCoord + 1, currentCell->_yCoord - 1, currentCell->_G + 1.414, currentCell);

			for (unsigned int i = 0; i < this->_openList.size(); ++i) {
				if (currentCell->_id == this->_openList[i]->_id) {
					this->_openList.erase(this->_openList.begin() + 1);
				}
			}
		}
	}
}

Point PathPlanner::nextPathPos() {
	int index = 1;

	Point nextPos;
	nextPos.x = this->_pathToGoal[this->_pathToGoal.size() - index]->x;
	nextPos.y = this->_pathToGoal[this->_pathToGoal.size() - index]->y;



	return nextPos;
}
