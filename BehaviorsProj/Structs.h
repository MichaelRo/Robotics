/*
 * Structs.h
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#define METER_TO_CM(meter) (meter * 100)

#include "Helper.h"

#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Structs {
public:
	struct Point {
	private:
		int _x;
		int _y;

	public :
		Point();
		Point (int x, int y);

		int getX();
		void setX(int x);
		int getY();
		void setY(int y);

		float distanceBetweenPoints(Point point);
		float manhattanDistance(Point point);
		float diagonalDistance(Point point);
		float squaredEuclideanDistance(Point point);

		Point robotPointToRealPoint();
		Point realPointToRobotPoint();
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
		Point operator/(float & number) const;
		Point operator*(const int & number) const;
		void operator=(const Point & point);
	};

	struct Location{
	private:
		float _x;
		float _y;
		float _yaw;

	public:
		Location();
		Location(float x, float y, float yaw = 0);
		Location(Point p, float yaw = 0);

		float getX();
		void setX(float x);
		float getY();
		void setY(float y);
		float getYaw();
		void setYaw(float yaw);

		Location robotLocationToRealLocation();
		Location realLocationToRobotLocation();

		Point pointValue();
		string toString();

		bool operator==(const Location & location) const;
		bool operator!=(const Location & location) const;
		Location operator+(const Location & location) const;
		Location operator-(const Location & location) const;
		void operator=(const Location & location);
	};

	struct Node {
	private:
		Point _point;
		float _g; // The cost until this search cell g(x)
		float _h; // The expected cost to the goal h(x)
		float _turnFactor;
		float _wallFactor;

	public :
		Node();
		Node(Point p, float GGrade);

		Point getPoint();
		void setPoint(Point point);
		float getG();
		void setG(float g);
		float getH();
		float getF();
		float getTurnFactor();
		void setTurnFactor(float turnFactor);
		float getWallFactor();
		void setWallFactor(float wallFactor);

		void calcHGrade(Point goal);
	};

	struct Size {
	private:
		int _width;
		int _height;

	public:
		Size();
		Size(int width, int height);

		int getWidth();
		void setWidth(int width);
		int getHeight();
		void setHeight(int height);

		string toString();

		bool operator==(const Size & size) const;
		bool operator!=(const Size & size) const;
		Size operator+(const Size & size) const;
		Size operator-(const Size & size) const;
		void operator=(const Size & size);
	};

	struct ConfigurationProperty {
	private:
		string _token;
		string _value;

	public:
		string getToken();
		string getValue();
		void setValue(string value);

		ConfigurationProperty(string token, string value);
	};
};

#endif
