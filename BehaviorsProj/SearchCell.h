/*
 * SearchCell.h
 *
 *  Created on: Jun 16, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include <math.h>
#include "Map.h"

using namespace std;

struct SearchCell {
public :
	int _xCoord, _yCoord;
	int _id;
	SearchCell* _parent;
	float _G; // The cost until this search cell g(x)
	float _H; // The expected cost to the goal h(x)

	SearchCell() {
		_parent = 0;
		SearchCell(0, 0, _parent);
	}

	SearchCell(int x, int y, SearchCell* parent = 0) {
		_xCoord = x;
		_yCoord = y;
		_parent = parent;
		_id = x * Map::MAP_COLUMNS + y;
		_G = 0;
		_H = 0;
	}

	float getF() {
		return this->_G + this->_H;
	}

	float ManhattanDistance(SearchCell* goal) {
		float x = (float) (fabs(this->_xCoord - goal->_xCoord));
		float y = (float) (fabs(this->_yCoord - goal->_yCoord));

		return x+y;
	}
};

struct Point {
public :
	int x;
	int y;

	Point() {
		x = 0;
		y = 0;
	}

	Point (int xCoord, int yCoord) {
		x = xCoord;
		y = yCoord;
	}
};
