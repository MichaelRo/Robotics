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
#include "WaypointsManager.h"

int main (int argc, const char * argv[]){
	/*Robot igal("localhost",6665);
	ConfigurationManager configurationManager("/home/colman/Documents/RoboticsFinalProj/PcBotWorld/parameters.txt");
	Manager manager(&configurationManager, &igal);
	manager.run();*/

	ConfigurationManager* conf = new ConfigurationManager("/home/colman/Documents/conf/parameters.txt");

	Map* map = new Map(conf);

	map->loadMap("/home/colman/Documents/conf/roboticLabMap.png");
	map->saveMap("originalMapMatrix.png");

	map->padMapObstacles(conf->getRobotSize()->_height / conf->getGridResolutionCM());
	map->saveMap("paddedMapMatrix.png");

	Structs::Point startPoint = conf->getRobotStartLocation()->pointValue();
	Structs::Point endPoint = conf->getRobotGoalLocation()->pointValue();

	PathPlanner pathPlanner = PathPlanner(map, &startPoint, &endPoint);
	list<Structs::Point> route = pathPlanner.performAStar();
	map->markRoute(route);

	map->saveMap("aStarMap.png");

	list<Structs::Point> wayPoints = WaypointsManager(route).getWaypoints();
	map->markWayPoints(wayPoints);

	map->saveMap("wayPointsMap.png");

	Structs::Location * robotStartLocation = conf->getRobotStartLocation();
	Structs::Location * robotGoalLocation = conf->getRobotGoalLocation();

	map->setCellValue(robotStartLocation->_x, robotStartLocation->_y, Map::START_LOCATION_CELL);
	map->setCellValue(robotGoalLocation->_x, robotGoalLocation->_y, Map::GOAL_LOCATION_CELL);

	map->saveMap("allPointsMap.png");
}
