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

	Structs::Point startPoint = _configurationManager->getRobotStartLocation().pointValue() / (_map->getGridMapResolutionRatio() / 2);
	Structs::Point endPoint = _configurationManager->getRobotGoalLocation().pointValue() / (_map->getGridMapResolutionRatio() / 2);
	_pathPlanner = new PathPlanner(_map, startPoint, endPoint);

	list<Structs::Point> route = _pathPlanner->performAStar();
	_map->markRoute(route, _map->getGridResolution());
	cout << "The route size is: " << route.size() << ", ";

	_waypointsManager = new WaypointsManager(route, _map);
	list<Structs::Point> wayPoints = _waypointsManager->getWaypoints(WaypointsManager::WAYPOINT_FOR_GRID);
	_map->markWayPoints(wayPoints, _map->getGridResolution());
	cout << wayPoints.size() << " of these are waypoints." << endl;

	_map->markStartPoint(startPoint, _map->getGridResolution());
	_map->markGoalPoint(endPoint, _map->getGridResolution());

	_map->saveMap("allPointsMap.png");

	_mapForRobot = new MapForRobot(_map);

	Structs::Location realRobotStartLocation(startPoint, _configurationManager->getRobotStartLocation().getYaw());
	_robot->setRobotLocation(realRobotStartLocation.realLocationToRobotLocation());

	_robot->Read();
	_localizationManager = new LocalizationManager(realRobotStartLocation, _mapForRobot);

	_movementManager = new MovementManager(_robot, _localizationManager, _waypointsManager);
	_movementManager->start();
}

Map * Manager::initializeMap() {
	Map* map = new Map(_configurationManager);

	map->loadMap("Simulation/roboticLabMap.png");
	map->saveMap("originalMapGrid.png");

	map->padMapObstacles(_configurationManager->getRobotSize().getHeight() / map->getGridResolution());
	map->saveMap("paddedMapGrid.png");

	return map;
}
