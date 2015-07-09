/*
 * Manager.cpp
 *
 *  Created on: June 29, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Manager.h"

Manager::~Manager() {
//	delete _movementManager;
//	delete _localizationManager;
//	delete _waypointsManager;
//	delete _pathPlanner;
//	delete _map;
}

Manager::Manager(ConfigurationManager* configurationManager, Robot* robot) {
	_robot = robot;
	_configurationManager = configurationManager;
	_map = NULL;
	_waypointsManager = NULL;
	_pathPlanner = NULL;
	_localizationManager = NULL;
	_movementManager = NULL;
	_mapForRobot = NULL;
}

void Manager::run() {
	_map = initializeMap();

	list<Structs::Point> route = getRoute();
	_map->markRoute(route, _map->getGridResolution());
	cout << "The route size is: " << route.size() << ", ";

	_waypointsManager = new WaypointsManager(route, _map);
	list<Structs::Point> wayPoints = _waypointsManager->getWaypoints(WaypointsManager::WAYPOINT_FOR_GRID);
	_map->markWayPoints(wayPoints, _map->getGridResolution());
	cout << wayPoints.size() << " of these are waypoints." << endl;

	Structs::Location robotStartLocation = _configurationManager->getRobotStartLocation();
	Structs::Location robotGoalLocation = _configurationManager->getRobotGoalLocation();

	_map->setCellValue(robotStartLocation._x, robotStartLocation._y, Map::START_LOCATION_CELL, _map->getMapResolution());
	_map->setCellValue(robotGoalLocation._x, robotGoalLocation._y, Map::GOAL_LOCATION_CELL, _map->getMapResolution());

	_map->saveMap("allPointsMap.png");

	_mapForRobot = new MapForRobot(_map);

	// Check if the waypoints are really different than the points that the robot returns (the player)
	_robot->setRobotLocation(robotStartLocation);
//	_robot->setRobotPosition(robotStartLocation.pointValue() * 2.5, robotStartLocation._yaw);

	_robot->Read();
	_localizationManager = new LocalizationManager(robotStartLocation, _mapForRobot);

	_movementManager = new MovementManager(_robot, _localizationManager, _waypointsManager->getWaypoints(WaypointsManager::WAYPOINT_FOR_ROBOT));
	_movementManager->start();
}

Map * Manager::initializeMap() {
	Map* map = new Map(_configurationManager);

	map->loadMap("Simulation/roboticLabMap.png");
	map->saveMap("originalMapGrid.png");

	map->padMapObstacles(_configurationManager->getRobotSize()._height / map->getGridResolution());
	map->saveMap("paddedMapGrid.png");

	return map;
}

list<Structs::Point> Manager::getRoute() {
	Structs::Point startPoint = _configurationManager->getRobotStartLocation().pointValue();
	Structs::Point endPoint = _configurationManager->getRobotGoalLocation().pointValue();
	_pathPlanner = new PathPlanner(_map, startPoint, endPoint);

	return _pathPlanner->performAStar();
}
