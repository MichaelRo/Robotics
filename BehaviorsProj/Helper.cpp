/*
 * Helper.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Helper.h"

const string Helper::CONFIGURATION_FILE_PATH = "Simulation/parameters.txt";

const int Helper::BLACK_RGBA[]  = {0, 0, 0, 255};
const int Helper::WHITE_RGBA[]  = {255, 255, 255, 255};
const int Helper::BLUE_RGBA[] = {0, 0, 255, 255};
const int Helper::GREEN_RGBA[] = {0, 255, 0, 255};
const int Helper::RED_RGBA[] = {255, 0, 0, 255};
const int Helper::PINK_RGBA[] = {255, 0, 255, 255};
const int Helper::LIGHT_BLUE_RGBA[] = {0, 255, 255, 255};
const int Helper::YELLOW_RGBA[] = {255, 255, 0, 255};
const int Helper::GRAY_RGBA[] = {105, 105, 105, 255};
const int Helper::NO_COLOR[] = {0, 0, 0, 0};

const int* Helper::getRGBA(int color) {
	switch (color) {
		case Helper::Color::BLACK :
			return BLACK_RGBA;
		case Helper::Color::WHITE :
			return WHITE_RGBA;
		case Helper::Color::BLUE :
			return BLUE_RGBA;
		case Helper::Color::GREEN :
			return GREEN_RGBA;
		case Helper::Color::RED :
			return RED_RGBA;
		case Helper::Color::PINK :
			return PINK_RGBA;
		case Helper::Color::LIGHT_BLUE :
			return LIGHT_BLUE_RGBA;
		case Helper::Color::YELLOW :
			return YELLOW_RGBA;
		case Helper::Color::GRAY :
			return GRAY_RGBA;
		default :
			return NO_COLOR;
	}
}

int Helper::degreesToIndex(int degrees) {
	int indexDifference = degrees * (Helper::TOTAL_SCAN_SPAN / Helper::TOTAL_DEGREES);
	return (Helper::TOTAL_SCAN_SPAN / 2) + indexDifference;
}

int Helper::indexToDegrees(int index) {
	int relativeIndex = index - (Helper::TOTAL_SCAN_SPAN / 2);
	return relativeIndex / (Helper::TOTAL_SCAN_SPAN / Helper::TOTAL_DEGREES);
}

float Helper::degreesToRadians(float degrees) {
//	float yaw = (degrees > 180) ? degrees - 360 : degrees;
	float yaw = degrees;

	return (yaw * M_PI) / 180;
}

float Helper::radiansToDegrees(float radians) {
	float yaw = (radians * 180) / M_PI;

	return yaw;
//	return (yaw < 0) ? yaw + 360 : yaw;
}

string Helper::intToString (int number) {
	stringstream ss;
	ss << number;
	return ss.str();
}

string Helper::floatToString (float number) {
	stringstream ss;
	ss << number;
	return ss.str();
}
