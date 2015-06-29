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
#include <list>
#include <limits>

using namespace std;

PathPlanner::PathPlanner(void) {
	_goalCell = NULL;
	_startCell = NULL;
}

list<Structs::Point> PathPlanner::performAStar(Map *map , Structs::Point *startPoint, Structs::Point *endPoint) {
	Structs::SearchCell *startCell = new Structs::SearchCell(startPoint, NULL, 0);
	Structs::SearchCell *endCell = new Structs::SearchCell(endPoint, NULL, 0);
	_map = map;
	list<Structs::Point> retList;

	_openList.push_back(*startCell);

	while (!_openList.empty()) {
		Structs::SearchCell *currMinNode = extractMinNode(_openList);

		if (currMinNode->_point->x == endPoint->x && currMinNode->_point->y == endPoint->y) {
			// handle end;
		}

		list<Structs::SearchCell> neighbors;
		for (int rowsIndex = currMinNode->_point->x - 1; rowsIndex <= currMinNode->_point->x + 1; rowsIndex++) {
			if (!(rowsIndex < 0 || rowsIndex >= _map->getHeight())) {
				for (int columnsIndex = currMinNode->_point->y - 1; columnsIndex <= currMinNode->_point->y + 1; columnsIndex++) {
					if (!(columnsIndex < 0 || columnsIndex >= _map->getWidth())) {
						if (_map->getCellValue(rowsIndex, columnsIndex) == Map::FREE_CELL) {
							// need to CHANGE 0 to the distance between the current node to the current neighbor
							Structs::SearchCell *neighbor = new Structs::SearchCell(new Structs::Point(rowsIndex, columnsIndex), currMinNode, 0);
							neighbors.push_back(*neighbor);
						}
					}
				}
			}
		}
	}

	return retList;
}

Structs::SearchCell* PathPlanner::extractMinNode(list<Structs::SearchCell> list) {
	float minF = std::numeric_limits<float>::max();
	Structs::SearchCell *minFNode;

	for (std::list<Structs::SearchCell>::iterator nodesIterator = list.begin(); nodesIterator != list.end(); nodesIterator++) {
		Structs::SearchCell *currNode = nodesIterator.operator ->();
		if (currNode->getF() < minF) {
			minF = currNode->getF();
			minFNode = currNode;
		}
	}
	list.remove(*minFNode);
	return minFNode;
}

void PathPlanner::findPath(Point currentPos, Point targetPos) {

}


SearchCell* PathPlanner::getNextCell() {

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

PathPlanner::~PathPlanner(void) {

}
