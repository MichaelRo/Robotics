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
#include <tuple>
#include <limits>
#include <algorithm>

using namespace std;

PathPlanner::PathPlanner(void) {
	_goalCell = NULL;
	_startCell = NULL;
}

list<Structs::Point> PathPlanner::performAStar(Map *map ,Structs::Point *startPoint, Structs::Point *endPoint) {
	Structs::Node *startCell = Structs::Node(startPoint, NULL, 0);
	Structs::Node *endCell = Structs::Node(endPoint, NULL, 0);
	_map = map;

	_openList.push_back(*startCell);

	while (!_openList.empty()) {
		Structs::Node *currMinNode = extractMinNode(_openList);

		// if we arrived the end point
		if (currMinNode->_point->x == endPoint->x && currMinNode->_point->y == endPoint->y) {
			return reconstruct_path(*currMinNode, *startPoint);
		}
		_closedList.push_back(*currMinNode);

		list<Structs::Node> neighbors = getNeighbors(currMinNode);
		for (std::list<Structs::Node>::iterator nodesIterator = neighbors.begin(); nodesIterator != neighbors.end(); nodesIterator++) {
			Structs::Node *currNeighbor = nodesIterator.operator ->();
			if ((std::find(_closedList.begin(), _closedList.end(), currNeighbor) != _closedList.end())) {
				continue;
			}

			float tempNeighborGGrade = currMinNode->_G + GRADE_FACTOR;
			if ((!(std::find(_openList.begin(), _openList.end(), currNeighbor) != _openList.end())) || tempNeighborGGrade < currNeighbor->_G) {
				currNeighbor->_parent = currMinNode;
				currNeighbor->_G = tempNeighborGGrade;
				currNeighbor->calcHGrade(endPoint);
				if (!(std::find(_openList.begin(), _openList.end(), currNeighbor) != _openList.end())) {
					_openList.push_back(*currNeighbor);
				}
			}
		}
	}

	return NULL;
}

list<Structs::Node> PathPlanner::getNeighbors(Structs::Node* node) {
	list<Structs::Node> neighbors;
	for (int rowsIndex = node->_point->x - 1; rowsIndex <= node->_point->x + 1;	rowsIndex++) {
		if (!(rowsIndex < 0 || rowsIndex >= _map->getHeight())) {
			for (int columnsIndex = node->_point->y - 1; columnsIndex <= node->_point->y + 1; columnsIndex++) {
				if (!(columnsIndex < 0 || columnsIndex >= _map->getWidth())) {
					if (_map->getCellValue(rowsIndex, columnsIndex) == Map::FREE_CELL) {
						// need to CHANGE 0 to the distance between the current node to the current neighbor
						Structs::Node* neighbor = Structs::Node(Structs::Point(rowsIndex, columnsIndex), node, node->_G + GRADE_FACTOR);
						neighbors.push_back(*neighbor);
					}
				}
			}
		}
	}
	return neighbors;
}

Structs::Node* PathPlanner::extractMinNode(list<Structs::Node> list) {
	float minF = std::numeric_limits<float>::max();
	Structs::Node *minFNode;

	for (std::list<Structs::Node>::iterator nodesIterator = list.begin(); nodesIterator != list.end(); nodesIterator++) {
		Structs::Node *currNode = nodesIterator.operator ->();
		if (currNode->getF() < minF) {
			minF = currNode->getF();
			minFNode = currNode;
		}
	}
	list.remove(*minFNode);
	return minFNode;
}

list<Structs::Point> PathPlanner::reconstruct_path(Structs::Node endNode, Structs::Point startPoint) {

	return NULL;
}

PathPlanner::~PathPlanner(void) {

}
