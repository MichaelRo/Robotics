/*
 * main.cpp
 *
 *  Created on: June 13, 2015
 *      Author: user
 */
#include "Robot.h"
#include "Manager.h"
#include "Map.h"
#include "Plans/PlnObstacleAvoid.h"

int main (int argc, const char * argv[])
{
//	Robot robot("localhost",6665);
//	PlnObstacleAvoid plnOA(&robot);
//	Manager manager(&robot, &plnOA);
//	manager.run();

	Map* m = new Map();

	m->readMap();
	m->printMap("originalMapMatrix.txt");

	m->padMapObstacles(4);
	m->printMap("paddedMapMatrix.txt");
}
