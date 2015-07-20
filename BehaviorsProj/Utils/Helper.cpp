/*
 * Helper.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Helper.h"

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
		case Globals::Color::BLACK :
			return BLACK_RGBA;
		case Globals::Color::WHITE :
			return WHITE_RGBA;
		case Globals::Color::BLUE :
			return BLUE_RGBA;
		case Globals::Color::GREEN :
			return GREEN_RGBA;
		case Globals::Color::RED :
			return RED_RGBA;
		case Globals::Color::PINK :
			return PINK_RGBA;
		case Globals::Color::LIGHT_BLUE :
			return LIGHT_BLUE_RGBA;
		case Globals::Color::YELLOW :
			return YELLOW_RGBA;
		case Globals::Color::GRAY :
			return GRAY_RGBA;
		default :
			return NO_COLOR;
	}
}

int Helper::degreesToIndex(int degrees) {
	return degrees * (Globals::TOTAL_SCAN_SPAN / Globals::TOTAL_DEGREES);
}

int Helper::indexToDegrees(int index) {
	return index * (Globals::TOTAL_DEGREES / Globals::TOTAL_SCAN_SPAN);
}

double Helper::degreesToRadians(double degrees) {
	double yaw = degrees;

	return (yaw * M_PI) / 180;
}

double Helper::radiansToDegrees(double radians) {
	double yaw = (radians * 180) / M_PI;

	return yaw;
}

string Helper::intToString (int number) {
	stringstream ss;
	ss << number;
	return ss.str();
}

string Helper::doubleToString (double number) {
	stringstream ss;
	ss << number;
	return ss.str();
}
