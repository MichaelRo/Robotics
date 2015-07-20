/*
 * Structs.h
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#define METER_TO_CM(meter) (meter * 100)

#include "../Utils/Helper.h"

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

		double distanceBetweenPoints(Point point);
		double manhattanDistance(Point point);
		double diagonalDistance(Point point);
		double squaredEuclideanDistance(Point point);

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
		Point operator/(double & number) const;
		Point operator*(const int & number) const;
		void operator=(const Point & point);
	};

	struct Location{
	private:
		double _x;
		double _y;
		double _yaw;

	public:
		Location();
		Location(double x, double y, double yaw = 0);
		Location(Point p, double yaw = 0);

		double getX();
		void setX(double x);
		double getY();
		void setY(double y);
		double getYaw();
		void setYaw(double yaw);

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
		double _g; // The cost until this search cell g(x)
		double _h; // The expected cost to the goal h(x)
		double _turnFactor;
		double _wallFactor;

	public :
		Node();
		Node(Point p, double GGrade);

		Point getPoint();
		void setPoint(Point point);
		double getG();
		void setG(double g);
		double getH();
		double getF();
		double getTurnFactor();
		void setTurnFactor(double turnFactor);
		double getWallFactor();
		void setWallFactor(double wallFactor);

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
