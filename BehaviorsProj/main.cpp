/*
 * main.cpp
 *
 *  Created on: June 13, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */
#include "Robot.h"
#include "ConfigurationManager.h"
#include "Map.h"
#include "PathPlanner.h"
#include "WaypointsManager.h"
#include "Manager.h"

int main (int argc, const char * argv[]){
	Robot igal("localhost",6665);
	Manager* manager = new Manager(&igal);
	manager->run();

//	ConfigurationManager* conf = ConfigurationManager::getInstance();
//
//	Map* map = new Map();
//
//	map->loadMap("Simulation/roboticLabMap.png");
//	map->saveMap("originalMapMatrix.png");
//
//	map->padMapObstacles(conf->getRobotSize().getHeight() / conf->getGridResolutionCM());
//	map->saveMap("paddedMapMatrix.png");
//
//	Structs::Point startPoint = conf->getRobotStartLocation().pointValue() / (map->getGridMapResolutionRatio() / 2);
//	Structs::Point endPoint = conf->getRobotGoalLocation().pointValue() / (map->getGridMapResolutionRatio() / 2);
//
//	PathPlanner pathPlanner = PathPlanner(map, startPoint, endPoint);
//	list<Structs::Point> route = pathPlanner.performAStar();
//	cout << "The route size is: " << route.size() << ", ";
//	map->markRoute(route, map->getGridResolution());
//
//	map->saveMap("aStarMap.png");
//
//	WaypointsManager * waypointsManager = new WaypointsManager(route, map);
//	list<Structs::Point> wayPoints = waypointsManager->getWaypoints(WaypointsManager::WAYPOINT_FOR_GRID);
//	cout << wayPoints.size() << " of these are waypoints." << endl;
//	map->markWayPoints(wayPoints, map->getGridResolution());
//
//	map->saveMap("wayPointsMap.png");
//
//	map->markStartPoint(startPoint, map->getGridResolution());
//	map->markGoalPoint(endPoint, map->getGridResolution());
//
//	map->saveMap("allPointsMap.png");
}
