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

	return _map->getCellValue(mapColumn, mapRow, _map->getMapResolution());
}
