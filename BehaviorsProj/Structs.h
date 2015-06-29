/*
 * Structs.h
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <string>
#include <math.h>

using namespace std;

class Structs {
public:
	struct Location{
		float x;
		float y;
		float yaw = 0;

		Location();
		Location(float x, float y, float yaw = 0);
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

		Point (Point *p) {
			x = p->x;
			y = p->y;
		}
	};

	struct SearchCell {
	public :
		Point* _point;
		SearchCell* _parent;
		float _G; // The cost until this search cell g(x)
		float _H; // The expected cost to the goal h(x)

		SearchCell() {
			_point = NULL;
			_parent = NULL;
			_G = 0;
			_H = 0;
		}

		SearchCell(Point *p, SearchCell *parent, float GGrade) {
			_point = new Point(p);
			_parent = parent;
			_G = GGrade;
			_H = 0;
		}

		float getF() {
			return this->_G + this->_H;
		}

		float ManhattanDistance(SearchCell* goal) {
			float x = (float) (fabs(_point->x - goal->_point->x));
			float y = (float) (fabs(_point->y - goal->_point->y));

			return x+y;
		}
	};

	struct Size {
		int width;
		int height;

		Size();
		Size(int width, int height);
	};

	struct ConfigurationProperty {
		string token;
		string value;

		ConfigurationProperty(string token, string value);
	};
};

#endif
