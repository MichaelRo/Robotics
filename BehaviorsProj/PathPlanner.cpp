/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "PathPlanner.h"

using namespace std;

PathPlanner::~PathPlanner(void) {
	delete _map;
}

PathPlanner::PathPlanner(Map * map, Structs::Point * startPoint, Structs::Point * endPoint) {
	_map = map;
	_startPoint = *startPoint / (map->getGridMapResolutionRatio() / 2);
	_endPoint = *endPoint / (map->getGridMapResolutionRatio() / 2);
}

list<Structs::Point> PathPlanner::performAStar() {
	list<Structs::Point> defRetList;
	Structs::Node startNode(_startPoint, NULL, 0);
	startNode.calcHGrade(&_endPoint);

	map<int,bool> openMap;
	map<int,bool> closedMap;

	_openQueue.push(startNode);
	openMap[_startPoint.hashCode()] = true;
//	_parentsMap[_startPoint.hashCode()] = Structs::Point(-1,-1);

	while (!_openQueue.empty()) {
		Structs::Node currMinNode = _openQueue.top();
		cout << "open list size is: " << _openQueue.size() << endl;

		// if we arrived the end point
		if (currMinNode._point == _endPoint) {
			return reconstruct_path(currMinNode._point);
		}
		_openQueue.pop();
		openMap[currMinNode._point.hashCode()] = false;
		closedMap[currMinNode._point.hashCode()] = true;
		defRetList.push_back(currMinNode._point);
		cout << "this node entered the closed list " << currMinNode._point._x << ", " << currMinNode._point._y << endl;

		cout << "curr Min Node: " << currMinNode._point._x << ", " << currMinNode._point._y << endl;;

		// get the neighbors of the current node and iterate it
		list<Structs::Node> neighbors = getNeighbors(&currMinNode);
		for (std::list<Structs::Node>::iterator nodesIterator = neighbors.begin(); nodesIterator != neighbors.end(); nodesIterator++) {
			Structs::Node *currNeighbor = nodesIterator.operator ->();
			// if we already finished dealing with this neighbor we continue
			if (closedMap[currNeighbor->_point.hashCode()]) {
				cout << "this neighbor skipped because it is already in the closed list " << currNeighbor->_point._x << ", " << currNeighbor->_point._y << endl;
				continue;
			}

			float tempNeighborGGrade = currMinNode._g + currMinNode._point.distanceBetweenPoints(&(currNeighbor->_point));

			// if we haven't visit this neighbor or if the grade that we calculated is less than what the neighbor have
			if (!openMap[currNeighbor->_point.hashCode()] || tempNeighborGGrade < currNeighbor->_g) {
				// set parent node and grades
				currNeighbor->_parent = &currMinNode;
				_parentsMap[currNeighbor->_point.hashCode()] = currMinNode._point;
				currNeighbor->_g = tempNeighborGGrade;
				currNeighbor->calcHGrade(&_endPoint);

				cout << "open queue size is: " << _openQueue.size() << endl;

				// if this neighbor is not in the open list, add it.
				cout << "trying to add: " << currNeighbor->_point._x << ", " << currNeighbor->_point._y << " to the openMap" << endl;
				if (!openMap[currNeighbor->_point.hashCode()]) {
					_openQueue.push(*currNeighbor);
					openMap[currNeighbor->_point.hashCode()] = true;
					cout << "node: " << currNeighbor->_point._x << ", " << currNeighbor->_point._y << " entered the openMap" << endl;
				}
				else {
					cout << "this neighbor not added because it is already in the open list " << currNeighbor->_point._x << ", " << currNeighbor->_point._y << endl;
				}
			}
		}

		neighbors.clear();
	}

	return defRetList;
}

// Reuse code with Map.cpp ?
list<Structs::Node> PathPlanner::getNeighbors(Structs::Node *node) {
	list<Structs::Node> neighbors;

	for (int rowsIndex = node->_point._y - 1; rowsIndex <= node->_point._y + 1; rowsIndex++) {
		if (!(rowsIndex < 0 || rowsIndex >= _map->getHeight())) {
			for (int columnsIndex = node->_point._x - 1; columnsIndex <= node->_point._x + 1; columnsIndex++) {
				if (!(columnsIndex < 0 || columnsIndex >= _map->getWidth())) {
					if ((_map->getCellValue(columnsIndex, rowsIndex, _map->getGridResolution()) == Map::FREE_CELL) &&
						!((node->_point._x == columnsIndex) && (node->_point._y == rowsIndex))) {
						Structs::Point neighborPoint(columnsIndex, rowsIndex);
						Structs::Node neighbor(&neighborPoint, NULL, std::numeric_limits<float>::max());

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
