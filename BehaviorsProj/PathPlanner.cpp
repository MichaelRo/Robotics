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
	delete _startPoint;
	delete _endPoint;
}

PathPlanner::PathPlanner(Map * map, Structs::Point * startPoint, Structs::Point * endPoint) {
	_map = new Map(map);

	_startPoint = new Structs::Point(startPoint->_x / (map->_gridMapResolutionRatio / 2),
									 startPoint->_y / (map->_gridMapResolutionRatio / 2));
	_endPoint = new Structs::Point(endPoint->_x / (map->_gridMapResolutionRatio / 2),
								   endPoint->_y / (map->_gridMapResolutionRatio / 2));
}

list<Structs::Point> PathPlanner::performAStar() {
	Structs::Node startNode(_startPoint, NULL, 0);
	startNode.calcHGrade(_endPoint);

	map<Structs::Node*,bool> openMap;
	map<Structs::Node*,bool> closedMap;


	// _openList.push_back(startNode);
	_openSet.push(&startNode);
	openMap[&startNode] = true;

	while (!_openSet.empty()) {
		Structs::Node *currMinNode = _openSet.top();
		cout << "open list size is: " << _openSet.size() << endl;

		// if we arrived the end point
		if (currMinNode->_point == _endPoint) {
			return reconstruct_path(*currMinNode);
		}
		_openSet.pop();
		openMap[currMinNode] = false;
		closedMap[currMinNode] = true;

		cout << "curr Min Node: " << currMinNode->_point._x << ", " << currMinNode->_point._y << endl;;

		// get the neighbors of the current node and iterate it
		list<Structs::Node> neighbors = getNeighbors(currMinNode);
		for (std::list<Structs::Node>::iterator nodesIterator = neighbors.begin(); nodesIterator != neighbors.end(); nodesIterator++) {
			Structs::Node *currNeighbor = nodesIterator.operator ->();
			// if we already finished dealing with this neighbor we continue
			if (closedMap[currNeighbor]) {
				continue;
			}

			float tempNeighborGGrade = currMinNode->_g + currMinNode->_point.distanceBetweenPoints(&currNeighbor->_point);

			// if we haven't visit this neighbor or if the grade that we calculated is less than what the neighbor have
			if (!openMap[currNeighbor] || tempNeighborGGrade < currNeighbor->_g) {
				// set parent node and grades
				currNeighbor->_parent = currMinNode;
				currNeighbor->_g = tempNeighborGGrade;
				currNeighbor->calcHGrade(_endPoint);

				cout << "open map size is: " << openMap.size() << endl;

				// if this neighbor is not in the open list, add it.
				cout << "trying to add: " << currNeighbor->_point._x << ", " << currNeighbor->_point._y << " to the openMap" << endl;
				if (!openMap[currNeighbor]) {
					_openSet.push(currNeighbor);
					openMap[currNeighbor] = true;
					cout << "node: " << currNeighbor->_point._x << ", " << currNeighbor->_point._y << " entered the openMap" << endl;
				}
			}
		}

		neighbors.clear();
	}

	return list<Structs::Point>();
}

// Reuse code with Map.cpp ?
list<Structs::Node> PathPlanner::getNeighbors(Structs::Node *node) {
	list<Structs::Node> neighbors;
	Structs::Node tempFatherNode = *node;

	for (int rowsIndex = node->_point._y - 1; rowsIndex <= node->_point._y + 1; rowsIndex++) {
		if (!(rowsIndex < 0 || rowsIndex >= _map->getHeight())) {
			for (int columnsIndex = node->_point._x - 1; columnsIndex <= node->_point._x + 1; columnsIndex++) {
				if (!(columnsIndex < 0 || columnsIndex >= _map->getWidth())) {
					if ((_map->getCellValue(columnsIndex, rowsIndex) == Map::FREE_CELL) &&
						!((node->_point._x == columnsIndex) && (node->_point._y == rowsIndex))) {
						Structs::Point neighborPoint(columnsIndex, rowsIndex);
						Structs::Node neighbor(&neighborPoint, NULL, std::numeric_limits<float>::max());

						neighbors.push_back(neighbor);
					}
				}
			}
		}
	}

	*node = tempFatherNode;

	return neighbors;
}

Structs::Node PathPlanner::extractMinNode(list<Structs::Node> * list) {
	float minF = std::numeric_limits<float>::max();
	std::list<Structs::Node>::iterator iteratorToErase;
	Structs::Node minFNode;

	for (std::list<Structs::Node>::iterator nodesIterator = list->begin(); nodesIterator != list->end(); nodesIterator++) {
		Structs::Node *currNode = nodesIterator.operator ->();
		if (currNode->getF() < minF) {
			minF = currNode->getF();
			minFNode = *currNode;
			iteratorToErase = nodesIterator;
		}
	}

	list->erase(iteratorToErase);

	return minFNode;
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

bool PathPlanner::listContains(list<Structs::Node> list, Structs::Node nodeToLookFor) {
	for (std::list<Structs::Node>::iterator nodesIterator = list.begin(); nodesIterator != list.end(); nodesIterator++) {
		Structs::Node *currNode = nodesIterator.operator ->();

		if (currNode->_point == nodeToLookFor._point)
			return true;
	}

	return false;
}
