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
#include <cmath>
#include <list>
#include <tuple>
#include <limits>
#include <algorithm>

using namespace std;

PathPlanner::~PathPlanner(void) {

}

PathPlanner::PathPlanner(void) {

}

list<Structs::Point> PathPlanner::performAStar(Map *map ,Structs::Point *startPoint, Structs::Point *endPoint) {
	Structs::Node startCell = Structs::Node(startPoint, NULL, 0);
	Map *coolMap = map;

	_openList.push_back(startCell);

	while (!_openList.empty()) {
		Structs::Node currMinNode = extractMinNode(_openList);

		// if we arrived the end point
		if (currMinNode._point->x == endPoint->x && currMinNode._point->y == endPoint->y) {
			return reconstruct_path(currMinNode);
		}
		_closedList.push_back(currMinNode);

		list<Structs::Node> neighbors = getNeighbors(&currMinNode, coolMap);
		for (std::list<Structs::Node>::iterator nodesIterator = neighbors.begin(); nodesIterator != neighbors.end(); nodesIterator++) {
			//////////////////////////////////////////////////////////////////////////////////////////
			//////////																		//////////
			//////////		Can't user std::find without implementing the == operator		//////////
			//////////																		//////////
			//////////////////////////////////////////////////////////////////////////////////////////

			Structs::Node *currNeighbor = nodesIterator.operator ->();
			if ((std::find(_closedList.begin(), _closedList.end(), currNeighbor) != _closedList.end())) {
				continue;
			}

			float tempNeighborGGrade = currMinNode._G + GRADE_FACTOR;
			if ((!(std::find(_openList.begin(), _openList.end(), currNeighbor) != _openList.end())) || tempNeighborGGrade < currNeighbor->_G) {
				currNeighbor->_parent = &currMinNode;
				currNeighbor->_G = tempNeighborGGrade;
				currNeighbor->calcHGrade(endPoint);
				if (!(std::find(_openList.begin(), _openList.end(), currNeighbor) != _openList.end())) {
					_openList.push_back(*currNeighbor);
				}
			}
		}
	}

	return list<Structs::Point>();
}

list<Structs::Node> PathPlanner::getNeighbors(Structs::Node* node, Map *map) {
	list<Structs::Node> neighbors;
	for (int rowsIndex = node->_point->x - 1; rowsIndex <= node->_point->x + 1;	rowsIndex++) {
		if (!(rowsIndex < 0 || rowsIndex >= map->getHeight())) {
			for (int columnsIndex = node->_point->y - 1; columnsIndex <= node->_point->y + 1; columnsIndex++) {
				if (!(columnsIndex < 0 || columnsIndex >= map->getWidth())) {
					if (map->getCellValue(rowsIndex, columnsIndex) == Map::FREE_CELL) {
						// need to CHANGE 0 to the distance between the current node to the current neighbor
						Structs::Point neighborPoint(rowsIndex, columnsIndex);
						Structs::Node neighbor(&neighborPoint, node, node->_G + GRADE_FACTOR);

						neighbors.push_back(neighbor);
					}
				}
			}
		}
	}
	return neighbors;
}

Structs::Node PathPlanner::extractMinNode(list<Structs::Node> list) {
	float minF = std::numeric_limits<float>::max();
	Structs::Node minFNode;

	for (std::list<Structs::Node>::iterator nodesIterator = list.begin(); nodesIterator != list.end(); nodesIterator++) {
		Structs::Node *currNode = nodesIterator.operator ->();
		if (currNode->getF() < minF) {
			minF = currNode->getF();
			minFNode = *currNode;

			// Maybe nodesIterator++ ?
			list.erase(nodesIterator);
		}
	}

	return minFNode;
}

void PathPlanner::clearOpenList() {
	_openList.clear();
}

void PathPlanner::clearPathToGoal() {
	_openList.clear();
}

list<Structs::Point> PathPlanner::reconstruct_path(Structs::Node endNode) {
	list<Structs::Point> path = list<Structs::Point>();
	Structs::Node * tempNode = &endNode;

	while (tempNode->_parent != NULL) {
		path.push_front(tempNode->_point);
		tempNode = tempNode->_parent;
	}

	path.push_front(tempNode->_point);

	return path;
}
