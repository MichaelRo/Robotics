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
		int _x;
		int _y;

		Point();
		Point (int x, int y);
		Point (Point *p);
	};

	struct Location{
		float _x;
		float _y;
		float _yaw;

		Location();
		Location(float x, float y, float yaw = 0);
		Point pointValue();
	};

	struct Node {
	public :
		Point* _point;
		Node* _parent;
		float _g; // The cost until this search cell g(x)
		float _h; // The expected cost to the goal h(x)

		Node();
		Node(Point *p, Node *parent, float GGrade);
		float getF();
		float calcHGrade(Point* goal);
	};

	struct Size {
		int _width;
		int _height;

		Size();
		Size(int width, int height);
	};

	struct ConfigurationProperty {
		string _token;
		string _value;

		ConfigurationProperty(string token, string value);
	};
};

#endif
