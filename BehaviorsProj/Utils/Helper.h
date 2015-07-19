/*
 * Helper.h
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef HELPER_H_
#define HELPER_H_

#include "../Framework/Structs.h"

#include <sstream>
#include <map>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

class Helper {
private:
	static const int BLACK_RGBA[];
	static const int WHITE_RGBA[];
	static const int BLUE_RGBA[];
	static const int GREEN_RGBA[];
	static const int RED_RGBA[];
	static const int PINK_RGBA[];
	static const int LIGHT_BLUE_RGBA[];
	static const int YELLOW_RGBA[];
	static const int GRAY_RGBA[];
	static const int NO_COLOR[];

public:
	enum Color {BLACK, WHITE, BLUE, GREEN, RED, PINK, LIGHT_BLUE, YELLOW, GRAY};
	enum Quarter {FIRST = 1, SECOND, THIRD, FOURTH};
	enum Direction {NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST, NONE};
	enum WaypointType {WAYPOINT_FOR_MAP, WAYPOINT_FOR_GRID};
	enum CellType {FREE_CELL = 0, OCCUPIED_CELL, UNKNOWN_CELL, START_LOCATION_CELL, GOAL_LOCATION_CELL, ROUTE_CELL, WAYPOINT_CELL, PADDING_CELL};

	static const string CONFIGURATION_FILE_PATH;
	const static char CONFIGURATION_DELIMITER = ':';

	static const int BYTES_PER_PIXEL_IN_PNG = 4;

	static const int TOTAL_PARTICLES_AMOUNT = 100;

	static constexpr float TOTAL_SCAN_SPAN = 666;
	static constexpr float TOTAL_DEGREES = 240;
	static constexpr float COMPROMISED_YAW = 2;
	static constexpr float LASER_MAX_DETECTION_RANGE = 4.095;
	static constexpr float COMPROMISED_DISTANCE = 9;
	static constexpr float MINIMUM_DISTANCE_FROM_WALL = 0.5;
	static constexpr float YAW_TURN_DELTA = 0.16;
	static constexpr float MOVEMENT_DELTA = 0.4;

	static const int * getRGBA(int color);

	static int indexToDegrees(int index);
	static int degreesToIndex(int degrees);
	static float degreesToRadians(float degrees);
	static float radiansToDegrees(float radians);
	static string intToString(int number);
	static string floatToString(float number);
};

#endif
