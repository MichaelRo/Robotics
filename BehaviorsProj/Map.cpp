/*
 * Map.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#include "Map.h"

Map::~Map() {
	// TODO Auto-generated destructor stub
}

Map::Map()
{
	for (int i = 0; i < MAP_ROWS ; i++)
	{
		for (int j = 0; j < MAP_COLUMNS ; j++)
		{
			_map[i][j] = UNKNOWN_CELL;
		}
	}
}

void Map::printMap()
{
	cout << "Printing Map: " << endl;
	for (int i = 0; i < MAP_ROWS ; i++)
	{
		for (int j = 0; j < MAP_COLUMNS ; j++)
		{
			cout << _map[i][j];
		}
		cout << endl;
	}
}

int Map::calculateXIndex(int x)
{
	return (x / MAP_RESOLUTION) + (MAP_COLUMNS / 2);
}

int Map::calculateYIndex(int y)
{
	return (y / MAP_RESOLUTION) - (MAP_ROWS / 2);
}

void Map::getMapCoordinates(double realX,double realY,int &mapX,int &mapY)
{
	mapX = calculateXIndex(realX);
	mapY = calculateYIndex(realY);
}

void Map::setCellValue(int x, int y, int value)
{
	int xIndex = calculateXIndex(x);
	int yIndex = calculateYIndex(y);
	_map[xIndex][yIndex] = value;
}

int Map::getCellValue(int x, int y)
{
	int xIndex = calculateXIndex(x);
	int yIndex = calculateYIndex(y);
	return _map[xIndex][yIndex];
}
