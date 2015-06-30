/*
 * Structs.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Structs.h"

Structs::Size::Size(int width, int height) {
	this->width = width;
	this->height = height;
}

Structs::Location::Location(float x, float y, float yaw) {
	this->x = x;
	this->y = y;
	this->yaw = yaw;
}

Structs::ConfigurationProperty::ConfigurationProperty(string token, string value) {
	this->token = token;
	this->value = value;
}

Structs::Point::Point() {
	x = 0;
	y = 0;
}

Structs::Point::Point (int xCoord, int yCoord) {
	x = xCoord;
	y = yCoord;
}

Structs::Point::Point (Point *p) {
	x = p->x;
	y = p->y;
}

