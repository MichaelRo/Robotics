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
		case BLACK :
			return BLACK_RGBA;
		case WHITE :
			return WHITE_RGBA;
		case BLUE :
			return BLUE_RGBA;
		case GREEN :
			return GREEN_RGBA;
		case RED :
			return RED_RGBA;
		case PINK :
			return PINK_RGBA;
		case LIGHT_BLUE :
			return LIGHT_BLUE_RGBA;
		case YELLOW :
			return YELLOW_RGBA;
		case GRAY :
			return GRAY_RGBA;
		default :
			return NO_COLOR;
	}
}

int Helper::DegreesToIndex(int degrees) {
	int indexDifference = degrees * Helper::DEGREES_INDEX_RATIO;
	return Helper::HALF_SCAN_SPAN + indexDifference;
}

int Helper::IndexToDegrees(int index) {
	int relativeIndex = index - Helper::HALF_SCAN_SPAN;
	return relativeIndex / Helper::DEGREES_INDEX_RATIO;
}
