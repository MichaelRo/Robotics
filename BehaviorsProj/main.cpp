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
#include "PathPlanner.h"

int main (int argc, const char * argv[]){
	/*Robot igal("localhost",6665);
	ConfigurationManager configurationManager("/home/colman/Documents/RoboticsFinalProj/PcBotWorld/parameters.txt");
	Manager manager(&configurationManager, &igal);
	manager.run();*/

	ConfigurationManager* conf = new ConfigurationManager("/home/colman/Documents/conf/parameters.txt");

		Map* m = new Map(conf);

		m->loadMap("/home/colman/Documents/conf/roboticLabMap.png");
		m->saveMap("originalMapMatrix.png");

		m->padMapObstacles(conf->getRobotSize()->_height / conf->getGridResolutionCM());
		m->saveMap("paddedMapMatrix.png");

		Structs::Point startPoint = conf->getRobotStartLocation()->pointValue();
		Structs::Point endPoint = conf->getRobotGoalLocation()->pointValue();

		m->markRoute(PathPlanner(m).performAStar(&startPoint, &endPoint));

		m->saveMap("aStarMap.png");
}
