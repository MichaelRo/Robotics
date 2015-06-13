/*
 * Map.h
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include "Helper.h"

using namespace std;

class Map
{
	static const int FREE_CELL = 0;
	static const int OCCUPIED_CELL = 1;
	static const int UNKNOWN_CELL = 2;

	static const int MAP_ROWS = 380;
	static const int MAP_COLUMNS = 550;
	static const int MAP_RESOLUTION = 2.5;
	static const int BYTES_PER_PIXEL = 4;

	int _map[MAP_ROWS][MAP_COLUMNS];
	int calculateXIndex(int x);
	int calculateYIndex(int y);

public:
	~Map();
	Map();
	void getMapCoordinates(double realX,double realY,int &mapX,int &mapY);
	int getCellValue(int x, int y);
	void setCellValue(int x, int y, int value);
	void printMap();
	void readMap();
};

#endif /* MAP_H_ */
