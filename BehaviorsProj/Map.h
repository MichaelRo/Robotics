/*
 * Map.h
 *
 *  Created on: Jun 9, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef MAP_H_
#define MAP_H_

#include "WriteToPng/lodepng.h"
#include "ConfigurationManager.h"
#include "Matrix.h"
#include "Helper.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <list>

using namespace std;

class Map {
private:
	static const int BYTES_PER_PIXEL = 4;

	int _width;
	int _height;
	ConfigurationManager * _configurationManager;
	Matrix* _grid;

	void setWidth(int width);
	void setHeight(int height);
	void padACell(int i, int j, Matrix * matrix, int factor);

	void markCells(list<Structs::Point> points, int cellType);

	static void pushRGBAColorToAVector(vector<unsigned char> * vector, int color);

public:
	static const int FREE_CELL = 0;
	static const int OCCUPIED_CELL = 1;
	static const int UNKNOWN_CELL = 2;
	static const int START_LOCATION_CELL = 3;
	static const int GOAL_LOCATION_CELL = 4;
	static const int ROUTE_CELL = 5;
	static const int WAYPOINT_CELL = 6;
	static const int PADDING_CELL = 8;

	float _gridMapResolutionRatio; // Maybe add getters and setters?

	~Map();
	Map(ConfigurationManager * configurationManager);
	Map(Map * map);

	int getWidth();
	int getHeight();
	int getCellValue(int column, int row);
	void setCellValue(int column, int row, int value);

	void printMap(string fileName);
	void loadMap(string pngFilePath);
	void saveMap(string pngFilePath);
	void padMapObstacles(int factor);
	void markRoute(list<Structs::Point> route);
	void markWayPoints(list<Structs::Point> wayPoints);
	void initializeGrid(int width, int height);
	void swapMap(Map * map);
};

#endif
