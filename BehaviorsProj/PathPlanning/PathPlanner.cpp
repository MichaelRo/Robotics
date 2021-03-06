/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "PathPlanner.h"

using namespace std;

/**
	Destructs PathPlanner.
*/
PathPlanner::~PathPlanner(void) {

}

/**
	Initializes the PathPlanner.

	@param map - the map of the place.
	@param startPoint - the startPoint of the robot.
	@param endPoint - the endPoint the robot need to arrived.
*/
PathPlanner::PathPlanner(Map * map, Structs::Point startPoint, Structs::Point endPoint) {
	_map = map;
	_startPoint = startPoint;
	_endPoint = endPoint;
}

/**
	This method implement A* algorithm in order to calculate the way the robot should go.

	@return - list of points the robot should go in order to arrived to the target in the fastest way.
 */
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
		if (currMinNode.getPoint() == _endPoint) {
			return reconstruct_path(currMinNode.getPoint());
		}

		_openQueue.pop();
		openMap[currMinNode.getPoint().hashCode()] = false;
		closedMap[currMinNode.getPoint().hashCode()] = true;

		// get the neighbors of the current node and iterate it
		list<Structs::Node> neighbors = getNeighbors(&currMinNode);
		for (list<Structs::Node>::iterator nodesIterator = neighbors.begin(); nodesIterator != neighbors.end(); nodesIterator++) {
			Structs::Node *currNeighbor = nodesIterator.operator ->();
			// if we already finished dealing with this neighbor we continue
			if (closedMap[currNeighbor->getPoint().hashCode()]) {
				continue;
			}

			double tempNeighborGGrade = (currMinNode.getG() + COST_BETWEEN_NODES)*0.05 + currNeighbor->getTurnFactor()*0.75 + currNeighbor->getWallFactor()*0.2;

			// if we haven't visit this neighbor or if the grade that we calculated is less than what the neighbor have
			if (!openMap[currNeighbor->getPoint().hashCode()] || tempNeighborGGrade < currNeighbor->getG()) {
				// set parent node and grades
				_parentsMap[currNeighbor->getPoint().hashCode()] = currMinNode.getPoint();
				currNeighbor->setG(tempNeighborGGrade);
				currNeighbor->calcHGrade(_endPoint);

				// if this neighbor is not in the open list, add it.
				if (!openMap[currNeighbor->getPoint().hashCode()]) {
					_openQueue.push(*currNeighbor);
					openMap[currNeighbor->getPoint().hashCode()] = true;
				}
			}
		}

		neighbors.clear();
	}

	return list<Structs::Point>();
}

/**
	This method get a node in the matrix and return his "neighbors" - the cells that close to the node.

	@param node - current node.
	@return - list of Node of the neighbors of the given node.
 */
list<Structs::Node> PathPlanner::getNeighbors(Structs::Node *node) {
	list<Structs::Node> neighbors;

	for (int rowsIndex = node->getPoint().getY() - 1; rowsIndex <= node->getPoint().getY() + 1; rowsIndex++) {
		if (!(rowsIndex < 0 || rowsIndex >= _map->getHeight())) {
			for (int columnsIndex = node->getPoint().getX() - 1; columnsIndex <= node->getPoint().getX() + 1; columnsIndex++) {
				if (!(columnsIndex < 0 || columnsIndex >= _map->getWidth())) {
					if ((_map->getCellValue(columnsIndex, rowsIndex, _map->getGridResolution()) == Globals::CellType::FREE_CELL) &&
						!((node->getPoint().getX() == columnsIndex) && (node->getPoint().getY() == rowsIndex))) {

						Structs::Point neighborPoint(columnsIndex, rowsIndex);
						Structs::Node neighbor(neighborPoint, std::numeric_limits<double>::max());
						// handle the direction factor
						if (node->getPoint() != _startPoint) {
							neighbor.setTurnFactor(calcDirectionFactor(_parentsMap[node->getPoint().hashCode()], node->getPoint(), neighborPoint));
						}

						neighbor.setWallFactor(calcWallFactor(neighborPoint, 3));

						neighbors.push_back(neighbor);
					}
				}
			}
		}
	}

	return neighbors;
}

/**
	This method reconstruct the path the robot should go by the end point.

	@param endPoint - the end point the robot need to arrived to.
	@return - list of points of the way the robot should go in order to arrived to the end point in the fastest way.
 */
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

/**
	This method calculate the direction factor.

	@param p1 - the point the robot was before the current point.
	@param p2 - the current point of the robot.
	@param p3 - the next point(point of neighbor of the current point).
	@return - the factor of the direction in order to decide which neighbor is the best.
 */
double PathPlanner::calcDirectionFactor(Structs::Point p1, Structs::Point p2, Structs::Point p3) {
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
			return 2;
		case 2: case 6:
		   return 3.9;
		case 3: case 5:
			return 8;
		case 4:
			return 30;
		default:
			return 0;
    }
}

/**
	This method calculate the wall factor.

	@param point - the next point(point of neighbor of the current point).
	@param wallDis - the distance from wall we check.
	@return - the factor of the wall distance.
 */
double PathPlanner::calcWallFactor(Structs::Point point, int wallDis) {
	int wallCounter = 0;
	for (int rowsIndex = point.getY() - wallDis; rowsIndex <= point.getY() + wallDis; rowsIndex++) {
		if (!(rowsIndex < 0 || rowsIndex >= _map->getHeight())) {
			for (int columnsIndex = point.getX() - wallDis; columnsIndex <= point.getX() + wallDis; columnsIndex++) {
				if (!(columnsIndex < 0 || columnsIndex >= _map->getWidth())) {
					if (_map->getCellValue(columnsIndex, rowsIndex, _map->getGridResolution()) == Globals::CellType::PADDING_CELL ||
						_map->getCellValue(columnsIndex, rowsIndex, _map->getGridResolution()) == Globals::CellType::OCCUPIED_CELL) {
						wallCounter++;
					}
				}
			}
		}
	}

	return wallCounter * 5;
}
