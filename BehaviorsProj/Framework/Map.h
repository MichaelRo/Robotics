/*
 * Map.h
 *
 *  Created on: Jun 9, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef MAP_H_
#define MAP_H_

#include "../WriteToPng/lodepng.h"
#include "../Utils/ConfigurationManager.h"
#include "../Framework/Matrix.h"
#include "../Utils/Helper.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;

class Map {
private:
	int _width;
	int _height;
	ConfigurationManager * _configurationManager;
	Matrix* _grid;
	float _gridResolution;
	float _mapResolution;

	void setWidth(int width);
	void setHeight(int height);
	void setGridResolution(float resolution);
	void setMapResolution(float resolution);
	void padACell(Structs::Point cellPoint, Matrix * matrix, int ratio);
	void markCells(list<Structs::Point> points, int cellType, float resolution);

	static list<Structs::Point> getCellsNeighbors(Structs::Point point, Matrix * matrix, int ratio);
	static void pushRGBAColorToAVector(vector<unsigned char> * vector, int color);

public:
	~Map();
	Map();
	Map(Map * map);

	int getWidth();
	int getHeight();
	float getGridResolution();
	float getMapResolution();
	float getGridMapResolutionRatio();
	int getCellValue(int column, int row, float resolution);
	int getCellValue(Structs::Point point, float resolution);
	int getCellValue(Structs::Location location, float resolution);
	void setCellValue(int column, int row, int value, float resolution);
	void setCellValue(Structs::Point point, int value, float resolution);
	void setCellValue(Structs::Location location, int value, float resolution);

	void printMap(string fileName);
	void loadMap(string pngFilePath);
	void saveMap(string pngFilePath);
	void padMapObstacles(int ratio);
	void markRoute(list<Structs::Point> route, float resolution);
	void markWayPoints(list<Structs::Point> wayPoints, float resolution);
	void markStartPoint(Structs::Point startPoint, float resolution);
	void markGoalPoint(Structs::Point goalPoint, float resolution);
	void initializeGrid(int width, int height);
	void swapMap(Map * map);
	list<Structs::Point> getCellsNeighborsByValue(Structs::Point point, list<int> neighborsValues, float resolution);
};

#endif