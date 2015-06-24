/*
 * Map.h
 *
 *  Created on: Jun 9, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <fstream>
#include "WriteToPng/lodepng.h"
#include "math.h"
#include "Matrix.h"
#include "ConfigurationManager.h"

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
	float _gridMapResolutionRatio;
	ConfigurationManager* _configurationManager;
	Matrix* _grid;

	void setWidth(int width);
	void setHeight(int height);
	void padACell(int i, int j, Matrix* matrix, int factor);

public:
	~Map();
	Map(int width, int height, ConfigurationManager* configurationManager);

	int getWidth();
	int getHeight();
	int getCellValue(int x, int y);
	void setCellValue(int x, int y, int value);

	void printMap(string fileName);
	void readMap();
	void padMapObstacles(int factor);
	void initResolutionFittedMap();
};

#endif /* MAP_H_ */
