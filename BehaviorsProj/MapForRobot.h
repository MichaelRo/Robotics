/*
 * MapForRobot.h
 *
 *  Created on: Jul 8, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef MAPFORROBOT_H_
#define MAPFORROBOT_H_

#include "Map.h"

using namespace std;

class MapForRobot {
private:
	Map * _map;

public:
	MapForRobot(Map * map);
	virtual ~MapForRobot();

	Map * getMap();

	int getWidth();
	int getHeight();
	float getGridResolution();
	float getMapResolution();
	float getGridMapResolutionRatio();
	int getCellValue(int column, int row);
	int getCellValue(Structs::Point point);
	int getCellValue(Structs::Location location);
};

#endif
