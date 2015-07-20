/*
 * Helper.h
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef HELPER_H_
#define HELPER_H_

#include "../Framework/Structs.h"
#include "Globals.h"

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
	static const int * getRGBA(int color);

	static int indexToDegrees(int index);
	static int degreesToIndex(int degrees);
	static double degreesToRadians(double degrees);
	static double radiansToDegrees(double radians);
	static string intToString(int number);
	static string doubleToString(double number);
};

#endif
