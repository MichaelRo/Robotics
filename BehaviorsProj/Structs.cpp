/*
 * Structs.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Structs.h"

Structs::Location::Location(float x, float y, float yaw) {
	this->x = x;
	this->y = y;
	this->yaw = yaw;
}

Structs::Size::Size(int width, int height) {
	this->width = width;
	this->height = height;
}

Structs::ConfigurationProperty::ConfigurationProperty(string token, string value) {
	this->token = token;
	this->value = value;
}

Structs::Point Structs::Location::pointValue() {
	return Structs::Point(x, y);
}
