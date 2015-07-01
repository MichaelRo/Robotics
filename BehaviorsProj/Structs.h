/*
 * Structs.h
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Structs {
public:
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

	struct Location{
			float x;
			float y;
			float yaw;

			Location();
			Location(float x, float y, float yaw = 0);
			Point pointValue();
		};

	struct Node {
	public :
		Point* _point;
		Node* _parent;
		float _G; // The cost until this search cell g(x)
		float _H; // The expected cost to the goal h(x)

		Node() {
			_point = NULL;
			_parent = NULL;
			_G = 0;
			_H = 0;
		}

		Node(Point *p, Node *parent, float GGrade) {
			_point = new Point(p);
			_parent = parent;
			_G = GGrade;
			_H = 0;
		}

		float getF() {
			return this->_G + this->_H;
		}

		float calcHGrade(Point* goal) {
			// ManhattanDistance
			float x = (float) (fabs(_point->x - goal->x));
			float y = (float) (fabs(_point->y - goal->y));

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
