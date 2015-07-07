/*
 * Structs.h
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include "Helper.h"

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

		float distanceBetweenPoints(Point point);
		float manhattanDistance(Point point);
		float diagonalDistance(Point point);
		int hashCode();
		string toString();

		bool operator==(const Point & point) const;
		bool operator!=(const Point & point) const;
		bool operator<(const Point & point) const;
		bool operator>(const Point & point) const;
		bool operator<=(const Point & point) const;
		bool operator>=(const Point & point) const;
		Point operator+(const Point & point) const;
		Point operator-(const Point & point) const;
		Point operator+(const int & number) const;
		Point operator-(const int & number) const;
		Point operator/(const int & number) const;
		Point operator*(const int & number) const;
		void operator=(const Point & point);
	};

	struct Location{
		float _x;
		float _y;
		float _yaw;

		Location();
		Location(float x, float y, float yaw = 0);
		Location(Point p, float yaw = 0);

		Point pointValue();
		string toString();

		bool operator==(const Location & location) const;
		bool operator!=(const Location & location) const;
		Location operator+(const Location & location) const;
		Location operator-(const Location & location) const;
		void operator=(const Location & location);
	};

	struct Node {
	public :
		Point _point;
		float _g; // The cost until this search cell g(x)
		float _h; // The expected cost to the goal h(x)
		float _turnFactor;

		Node();
		Node(Point p, float GGrade);

		float getF();
		void calcHGrade(Point goal);
	};

	struct Size {
		int _width;
		int _height;

		Size();
		Size(int width, int height);

		string toString();

		bool operator==(const Size & size) const;
		bool operator!=(const Size & size) const;
		Size operator+(const Size & size) const;
		Size operator-(const Size & size) const;
		void operator=(const Size & size);
	};

	struct ConfigurationProperty {
		string _token;
		string _value;

		ConfigurationProperty(string token, string value);
	};
};

#endif
