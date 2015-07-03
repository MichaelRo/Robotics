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

Structs::Point::Point(Point* p) {
	_x = p->_x;
	_y = p->_y;
}

float Structs::Point::distanceBetweenPoints(Point* p) {
	double aSide = pow(_x - p->_x, 2);
	double bSide = pow(_y - p->_y, 2);
	return sqrt(aSide + bSide);
}

Structs::Location::Location(float x, float y, float yaw) {
	this->_x = x;
	this->_y = y;
	this->_yaw = yaw;
}

Structs::Point Structs::Location::pointValue() {
	return Structs::Point(_x, _y);
}

Structs::Node::Node() {
	_point = NULL;
	_parent = NULL;
	_g = 0;
	_h = 0;
}

Structs::Node::Node(Point* p, Node* parent, float GGrade) {
	_point = new Point(p);
	_parent = parent;
	_g = GGrade;
	_h = 0;
}

float Structs::Node::getF() {
	return _g + _h;
}

void Structs::Node::calcHGrade(Point* goal) {
	// ManhattanDistance
	_h = _point->distanceBetweenPoints(goal);
}

Structs::Size::Size(int width, int height) {
	this->_width = width;
	this->_height = height;
}

Structs::ConfigurationProperty::ConfigurationProperty(string token, string value) {
	this->_token = token;
	this->_value = value;
}
