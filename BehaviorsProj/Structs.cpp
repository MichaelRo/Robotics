/*
 * Structs.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Structs.h"

Structs::Point::Point() {
	_x = 0;
	_y = 0;
}

Structs::Point::Point(int x, int y) {
	_x = x;
	_y = y;
}

Structs::Point::Point(Point * p) {
	_x = p->_x;
	_y = p->_y;
}

float Structs::Point::distanceBetweenPoints(Point * p) {
	double aSide = pow(_x - p->_x, 2);
	double bSide = pow(_y - p->_y, 2);
	return sqrt(aSide + bSide);
}

bool Structs::Point::operator ==(const Point & point) const {
	return (_x == point._x) && (_y == point._y);
}

bool Structs::Point::operator !=(const Point & point) const {
	return (_x != point._x) || (_y != point._y);
}

bool Structs::Point::operator <(const Point & point) const {
	return (_x < point._x) && (_y < point._y);
}

bool Structs::Point::operator >(const Point & point) const {
	return (_x > point._x) || (_y > point._y);
}

bool Structs::Point::operator <=(const Point & point) const {
	return (_x <= point._x) && (_y <= point._y);
}

bool Structs::Point::operator >=(const Point & point) const {
	return (_x >= point._x) || (_y >= point._y);
}

Structs::Location::Location(float x, float y, float yaw) {
	this->_x = x;
	this->_y = y;
	this->_yaw = yaw;
}

Structs::Point Structs::Location::pointValue() {
	return Structs::Point(_x, _y);
}

bool Structs::Location::operator ==(const Location & location) {
	return (_x == location._x) && (_y == location._y) && (_yaw == location._yaw);
}

bool Structs::Location::operator !=(const Location & location) {
	return (_x != location._x) || (_y != location._y) || (_yaw != location._yaw);
}

Structs::Node::Node() {
	_parent = NULL;
	_point = Point();
	_g = 0;
	_h = 0;
}

Structs::Node::Node(Point * p, Node * parent, float GGrade) {
	_parent = parent;
	_point = Point(p);
	_g = GGrade;
	_h = 0;
}

float Structs::Node::getF() {
	return _g + _h;
}

void Structs::Node::calcHGrade(Point * goal) {
	// ManhattanDistance
	_h = _point.distanceBetweenPoints(goal);
}

Structs::Size::Size(int width, int height) {
	this->_width = width;
	this->_height = height;
}

bool Structs::Size::operator ==(const Size & size) {
	return (_width == size._width) && (_height == size._height);
}

bool Structs::Size::operator !=(const Size & size) {
	return (_width != size._width) || (_height != size._height);
}

Structs::ConfigurationProperty::ConfigurationProperty(string token, string value) {
	this->_token = token;
	this->_value = value;
}
