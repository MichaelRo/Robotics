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
#include "Helper.h"

using namespace std;

class Map
{
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

	static void pushRGBAColorToAVector(vector<unsigned char> * vector, int color);

public:
	static const int FREE_CELL = 0;
	static const int OCCUPIED_CELL = 1;
	static const int UNKNOWN_CELL = 2;
	static const int START_LOCATION_CELL = 3;
	static const int GOAL_LOCATION_CELL = 4;
	static const int ROUTE_CELL = 5;

	~Map();
	Map(ConfigurationManager* configurationManager);

	int getWidth();
	int getHeight();
	int getCellValue(int x, int y);
	void setCellValue(int x, int y, int value);

	void printMap(string fileName);
	void loadMap(string pngFilePath);
	void saveMap(string pngFilePath);
	void padMapObstacles(int factor);

	void initializeGrid(int width, int height);
};

#endif /* MAP_H_ */
