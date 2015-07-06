/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "PathPlanner.h"
#include "WaypointsManager.h"

using namespace std;

PathPlanner::~PathPlanner(void) {
	delete _map;
}

PathPlanner::PathPlanner(Map * map, Structs::Point startPoint, Structs::Point endPoint) {
	_map = map;
	_startPoint = startPoint / (map->getGridMapResolutionRatio() / 2);
	_endPoint = endPoint / (map->getGridMapResolutionRatio() / 2);
}

list<Structs::Point> PathPlanner::performAStar() {
	Structs::Node startNode(_startPoint, 0);
	startNode.calcHGrade(_endPoint);

	map<int,bool> openMap;
	map<int,bool> closedMap;

	_openQueue.push(startNode);
	openMap[_startPoint.hashCode()] = true;

	while (!_openQueue.empty()) {
		Structs::Node currMinNode = _openQueue.top();

		// if we arrived the end point
		if (currMinNode._point == _endPoint) {
			return reconstruct_path(currMinNode._point);
		}
		_openQueue.pop();
		openMap[currMinNode._point.hashCode()] = false;
		closedMap[currMinNode._point.hashCode()] = true;

		// get the neighbors of the current node and iterate it
		list<Structs::Node> neighbors = getNeighbors(&currMinNode);
		for (list<Structs::Node>::iterator nodesIterator = neighbors.begin(); nodesIterator != neighbors.end(); nodesIterator++) {
			Structs::Node *currNeighbor = nodesIterator.operator ->();
			// if we already finished dealing with this neighbor we continue
			if (closedMap[currNeighbor->_point.hashCode()]) {
				continue;
			}

			float tempNeighborGGrade = currMinNode._g + COST_BETWEEN_NODES + currNeighbor->_turnFactor;

			// if we haven't visit this neighbor or if the grade that we calculated is less than what the neighbor have
			if (!openMap[currNeighbor->_point.hashCode()] || tempNeighborGGrade < currNeighbor->_g) {
				// set parent node and grades
				_parentsMap[currNeighbor->_point.hashCode()] = currMinNode._point;
				currNeighbor->_g = tempNeighborGGrade;
				currNeighbor->calcHGrade(_endPoint);

				// if this neighbor is not in the open list, add it.
				if (!openMap[currNeighbor->_point.hashCode()]) {
					_openQueue.push(*currNeighbor);
					openMap[currNeighbor->_point.hashCode()] = true;
				}
			}
		}

		neighbors.clear();
	}

	return list<Structs::Point>();
}

/**
 * this method get a node in the matrix and return his "neighbors" - the cells that close to the node.
 */
list<Structs::Node> PathPlanner::getNeighbors(Structs::Node *node) {
	list<Structs::Node> neighbors;

	for (int rowsIndex = node->_point._y - 1; rowsIndex <= node->_point._y + 1; rowsIndex++) {
		if (!(rowsIndex < 0 || rowsIndex >= _map->getHeight())) {
			for (int columnsIndex = node->_point._x - 1; columnsIndex <= node->_point._x + 1; columnsIndex++) {
				if (!(columnsIndex < 0 || columnsIndex >= _map->getWidth())) {
					if ((_map->getCellValue(columnsIndex, rowsIndex, _map->getGridResolution()) == Map::FREE_CELL) &&
						!((node->_point._x == columnsIndex) && (node->_point._y == rowsIndex))) {
						Structs::Point neighborPoint(columnsIndex, rowsIndex);
						Structs::Node neighbor(neighborPoint, std::numeric_limits<float>::max());
						// handle the direction factor
						if (node->_point != _startPoint) {
							neighbor._turnFactor = calcDirectionFactor(_parentsMap[node->_point.hashCode()], node->_point, neighborPoint);
						}

						neighbors.push_back(neighbor);
					}
				}
			}
		}
	}

	return neighbors;
}

list<Structs::Point> PathPlanner::reconstruct_path(Structs::Point endPoint) {
	list<Structs::Point> path = list<Structs::Point>();
	Structs::Point tempPoint= endPoint;

	while (_parentsMap[tempPoint.hashCode()] != _startPoint) {
		path.push_front(tempPoint);
		tempPoint = _parentsMap[tempPoint.hashCode()];
	}

	path.push_front(tempPoint);
	path.push_front(_parentsMap[tempPoint.hashCode()]);

	return path;
}

float PathPlanner::calcDirectionFactor(Structs::Point p1, Structs::Point p2, Structs::Point p3) {
	int firstDir = WaypointsManager::getDirection(p1,p2);
	int secondDir = WaypointsManager::getDirection(p2,p3);

	/**
	 * this switch case rate the direction by the previous direction
     * if the direction is the same (0 in the switch) we give it a good grade (0 is the perfect grade)
     * and than we grade it that way - the bigger the angle between directions the lower the grade will be.
	 */
	switch(abs(secondDir - firstDir) % 8) {
		case 0:
			return 0;
		case 1: case 7:
			return 0.2;
		case 2: case 6:
		   return 2;
		case 3: case 5:
			return 20;
		case 4:
			return 24;
		default:
			return 0;
    }
}
