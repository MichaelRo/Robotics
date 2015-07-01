/*
 * Manager.cpp
 *
 *  Created on: June 29, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Manager.h"

Manager::Manager(ConfigurationManager* configurationManager, Robot* robot) {
	_robot = robot;
	_configurationManager = configurationManager;
	_map = NULL;
	_waypointsManager = NULL;
	_pathPlanner = NULL;
	_localizationManager = NULL;
}

void Manager::run() {
	_map = initializeMap();

	_waypointsManager = new WaypointsManager(getRoute());

	runRobot();
}

Map * Manager::initializeMap() {
	Map* m = new Map(_configurationManager);

	m->loadMap("/home/colman/Documents/RoboticsFinalProj/PcBotWorld/roboticLabMap.png");
	m->printMap("originalMapMatrix.txt");

	m->padMapObstacles(_configurationManager->getRobotSize()->height / _configurationManager->getGridResolutionCM());
	m->printMap("paddedMapMatrix.txt");

	m->saveMap("paddedGrid.png");

	return m;
}

list<Structs::Point> Manager::getRoute() {
	Structs::Point startPoint = _configurationManager->getRobotStartLocation()->pointValue();
	Structs::Point endPoint = _configurationManager->getRobotGoalLocation()->pointValue();
	return _pathPlanner->performAStar(_map, &startPoint, &endPoint);
}

void Manager::runRobot() {
}

Manager::~Manager() {
	delete _robot;
	delete _configurationManager;
	delete _map;
	delete _pathPlanner;
	delete _waypointsManager;
	delete _localizationManager;
}
