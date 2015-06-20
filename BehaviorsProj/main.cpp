/*
 * main.cpp
 *
 *  Created on: June 13, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */
#include "Robot.h"
#include "ConfigurationManager.h"
#include "Map.h"
#include "Plans/PlnObstacleAvoid.h"

int main (int argc, const char * argv[])
{
//	Robot robot("localhost",6665);
//	PlnObstacleAvoid plnOA(&robot);
//	Manager manager(&robot, &plnOA);
//	manager.run();

	ConfigurationManager* conf = new ConfigurationManager("/home/colman/Documents/RoboticsFinalProj/PcBotWorld/parameters.txt");

	Map* m = new Map(550, 380, conf->getGridResolutionCM());

	m->readMap();
	m->printMap("originalMapMatrix.txt");

	m->padMapObstacles(12);
	m->printMap("paddedMapMatrix.txt");
}
