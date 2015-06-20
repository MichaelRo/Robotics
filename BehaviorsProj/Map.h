/*
 * Map.h
 *
 *  Created on: Jun 9, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include "Helper.h"
#include "WriteToPng/lodepng.h"
#include "math.h"
#include <fstream>

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

private:
	int _width;
	int _height;
	float _resolution;
	int _map[MAP_ROWS][MAP_COLUMNS];

	void padACell(int i, int j, int tempMap[MAP_ROWS][MAP_COLUMNS], int factor);

public:
	~Map();
	Map(int width, int height, float resolution);

	int getWidth();
	int getHeight();
	float getResolution();
	int getCellValue(int x, int y);
	void setCellValue(int x, int y, int value);

	void printMap(string fileName);
	void readMap();
	void padMapObstacles(int factor);
	void initResolutionFittedMap();
	int calculateXIndex(int x);
	int calculateYIndex(int y);
};

#endif /* MAP_H_ */
