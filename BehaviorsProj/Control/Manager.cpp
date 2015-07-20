/*
 * Manager.cpp
 *
 *  Created on: June 29, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Manager.h"

/**
	Destructs Manager.
*/
Manager::~Manager() {

}

/**
	Initializes the Manager.

	@param robot - initialize the robot at the manager object.
*/
Manager::Manager(Robot* robot) {
	_configurationManager = ConfigurationManager::getInstance();

	_robot = robot;
	_map = NULL;
	_waypointsManager = NULL;
	_pathPlanner = NULL;
	_localizationManager = NULL;
	_movementManager = NULL;
}

/**
  	this method run all activities of the robot.
 */
void Manager::run() {
	_map = initializeMap();

	Structs::Point startPoint = _configurationManager->getRobotStartLocation().pointValue() / (_map->getGridMapResolutionRatio() / 2);
	Structs::Point endPoint = _configurationManager->getRobotGoalLocation().pointValue() / (_map->getGridMapResolutionRatio() / 2);
	_pathPlanner = new PathPlanner(_map, startPoint, endPoint);

	list<Structs::Point> route = _pathPlanner->performAStar();
	_map->markRoute(route, _map->getGridResolution());

	_waypointsManager = new WaypointsManager(route, _map);
	list<Structs::Point> wayPoints = _waypointsManager->getWaypoints(Globals::WaypointType::WAYPOINT_FOR_GRID);
	_map->markWayPoints(wayPoints, _map->getGridResolution());

	_map->markStartPoint(startPoint, _map->getGridResolution());
	_map->markGoalPoint(endPoint, _map->getGridResolution());

	_map->saveMap("allPointsMap.png");

	Structs::Location realRobotStartLocation(_configurationManager->getRobotStartLocation().pointValue(), _configurationManager->getRobotStartLocation().getYaw());

	// Fixing Player's reading bug
	for(int i = 0; i < 15; i++) {
		_robot->setOdometry(realRobotStartLocation);
		_robot->Read();
	}

	_localizationManager = new LocalizationManager(realRobotStartLocation, _map);

	_movementManager = new MovementManager(_robot, _localizationManager, _waypointsManager);
	_movementManager->start();
}

/**
	This method return the map after load, save and pad.

	@return - Map after load, save and pad.
 */
Map * Manager::initializeMap() {
	Map* map = new Map();

	map->loadMap("Simulation/roboticLabMap.png");
	map->padMapObstacles(_configurationManager->getRobotSize().getHeight() / map->getGridResolution());

	return map;
}
