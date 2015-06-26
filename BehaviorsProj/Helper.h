/*
 * Helper.h
 *
 *  Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef HELPER_H_
#define HELPER_H_

#include <map>
#include <vector>

using namespace std;

class Helper
{
private:
	static const int BLACK_RGBA[];
	static const int WHITE_RGBA[];
	static const int BLUE_RGBA[];
	static const int GREEN_RGBA[];
	static const int RED_RGBA[];
	static const int PINK_RGBA[];
	static const int LIGHT_BLUE_RGBA[];
	static const int YELLOW_RGBA[];
	static const int NO_COLOR[];

public:
	static const int BLACK = 1;
	static const int WHITE = 2;
	static const int BLUE = 3;
	static const int GREEN = 4;
	static const int RED = 5;
	static const int PINK = 6;
	static const int LIGHT_BLUE = 7;
	static const int YELLOW = 8;

	const static int * getRGBA(int color);
};

#endif /* HELPER_H_ */
