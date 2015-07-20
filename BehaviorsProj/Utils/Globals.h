/*
 * Globals.h
 *
 *  Created on: Jul 19, 2015
 *      Author: colman
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <string>

using namespace std;

class Globals {
public:
	enum Color {BLACK, WHITE, BLUE, GREEN, RED, PINK, LIGHT_BLUE, YELLOW, GRAY};
	enum Quarter {FIRST = 1, SECOND, THIRD, FOURTH};
	enum Direction {NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST, NONE};
	enum WaypointType {WAYPOINT_FOR_MAP, WAYPOINT_FOR_GRID};
	enum CellType {FREE_CELL = 0, OCCUPIED_CELL, UNKNOWN_CELL, START_LOCATION_CELL, GOAL_LOCATION_CELL, ROUTE_CELL, WAYPOINT_CELL, PADDING_CELL};

	static const string CONFIGURATION_FILE_PATH;
	const static char CONFIGURATION_DELIMITER = ':';

	static const int BYTES_PER_PIXEL_IN_PNG = 4;

	static const int TOTAL_PARTICLES_AMOUNT = 200;
	static constexpr double BELIEF_THRESHOLD = 0.7;
	static constexpr double MAX_PARTICLES_RELATIVE_RATIO_CREATION = 0.05;
	static constexpr double MAX_PARTICLES_RELATIVE_YAW_CREATION = 0.05;

	static constexpr double TOTAL_SCAN_SPAN = 666;
	static constexpr double TOTAL_DEGREES = 240;
	static constexpr double COMPROMISED_YAW = 2;
	static constexpr double LASER_MAX_DETECTION_RANGE = 4.095;
	static constexpr double COMPROMISED_DISTANCE = 9;
	static constexpr double MINIMUM_DISTANCE_FROM_WALL = 0.5;
	static constexpr double YAW_TURN_DELTA = 0.16;
	static constexpr double MOVEMENT_DELTA = 0.4;

	Globals();
	virtual ~Globals();
};

#endif
