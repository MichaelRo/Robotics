/*
 * MapForRobot.cpp
 *
 *  Created on: Jul 8, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "MapForRobot.h"

MapForRobot::~MapForRobot() {

}

MapForRobot::MapForRobot(Map * map) {
	_map = map;
}

Map * MapForRobot::getMap() {
	return _map;
}

int MapForRobot::getWidth() {
	return _map->getWidth();
}

int MapForRobot::getHeight() {
	return _map->getHeight();
}

float MapForRobot::getGridResolution() {
	return _map->getGridResolution();
}

float MapForRobot::getMapResolution() {
	return _map->getMapResolution();
}

float MapForRobot::getGridMapResolutionRatio() {
	return _map->getGridMapResolutionRatio();
}

int MapForRobot::getCellValue(int column, int row) {
	// Because that the (0, 0) of the player is in the middle
	int mapColumn = column + (_map->getWidth() / 2);
	int mapRow = (row * (-1)) + (_map->getHeight() / 2);

	int cellValue = _map->getCellValue(mapColumn, mapRow, _map->getMapResolution());

	return ((cellValue == Map::GOAL_LOCATION_CELL) ||
			(cellValue == Map::START_LOCATION_CELL) ||
			(cellValue == Map::PADDING_CELL) ||
			(cellValue == Map::ROUTE_CELL) ||
			(cellValue == Map::WAYPOINT_CELL)) ? Map::FREE_CELL : cellValue;
}

int MapForRobot::getCellValue(Structs::Point point) {
	return getCellValue(point.getX(), point.getY());
}

int MapForRobot::getCellValue(Structs::Location location) {
	return getCellValue(location.getX(), location.getY());
}
