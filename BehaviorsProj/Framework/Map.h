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
	double _gridResolution;
	double _mapResolution;

	void setWidth(int width);
	void setHeight(int height);
	void setGridResolution(double resolution);
	void setMapResolution(double resolution);
	void padACell(Structs::Point cellPoint, Matrix * matrix, int ratio);
	void markCells(list<Structs::Point> points, int cellType, double resolution);

	static list<Structs::Point> getCellsNeighbors(Structs::Point point, Matrix * matrix, int ratio);
	static void pushRGBAColorToAVector(vector<unsigned char> * vector, int color);

public:
	~Map();
	Map();
	Map(Map * map);

	int getWidth();
	int getHeight();
	double getGridResolution();
	double getMapResolution();
	double getGridMapResolutionRatio();
	int getCellValue(int column, int row, double resolution);
	int getCellValue(Structs::Point point, double resolution);
	int getCellValue(Structs::Location location, double resolution);
	void setCellValue(int column, int row, int value, double resolution);
	void setCellValue(Structs::Point point, int value, double resolution);
	void setCellValue(Structs::Location location, int value, double resolution);

	void printMap(string fileName);
	void loadMap(string pngFilePath);
	void saveMap(string pngFilePath);
	void padMapObstacles(int ratio);
	void markRoute(list<Structs::Point> route, double resolution);
	void markWayPoints(list<Structs::Point> wayPoints, double resolution);
	void markStartPoint(Structs::Point startPoint, double resolution);
	void markGoalPoint(Structs::Point goalPoint, double resolution);
	void initializeGrid(int width, int height);
	void swapMap(Map * map);
};

#endif
