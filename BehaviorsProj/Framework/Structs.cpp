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

int Structs::Point::getX() {
	return _x;
}

void Structs::Point::setX(int x) {
	_x = x;
}

int Structs::Point::getY() {
	return _y;
}

void Structs::Point::setY(int y) {
	_y = y;
}

double Structs::Point::distanceBetweenPoints(Point point) {
	double aSide = pow(_x - point.getX(), 2);
	double bSide = pow(_y - point.getY(), 2);
	return sqrt(aSide + bSide);
}

double Structs::Point::manhattanDistance(Point point) {
	double xSide = abs(_x - point.getX());
	double ySide = abs(_y - point.getY());

	return (xSide + ySide);
}

double Structs::Point::diagonalDistance(Point point) {
	double xSide = abs(_x - point.getX());
	double ySide = abs(_y - point.getY());

	return max(xSide, ySide);
}

double Structs::Point::squaredEuclideanDistance(Point point) {
	double xSide = abs(_x - point.getX());
	double ySide = abs(_y - point.getY());

	return pow(xSide, 2) + pow(ySide, 2);
}

int Structs::Point::hashCode() {
	int xPart = _x;
	int yPart = _y;

	int temp = yPart;

	while (temp >0)
	{
	    temp /= 10;
	    xPart *= 10;
	}

	return xPart + yPart;
}

string Structs::Point::toString() {
	return "(" + Helper::intToString(_x) + ", " + Helper::intToString(_y) + ")";
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
	return (_x > point._x) && (_y > point._y);
}

bool Structs::Point::operator <=(const Point & point) const {
	return (_x <= point._x) && (_y <= point._y);
}

bool Structs::Point::operator >=(const Point & point) const {
	return (_x >= point._x) && (_y >= point._y);
}

Structs::Point Structs::Point::operator +(const Point & point) const {
	return Structs::Point(_x + point._x, _y + point._y);
}

Structs::Point Structs::Point::operator -(const Point & point) const {
	return Structs::Point(_x - point._x, _y - point._y);
}

Structs::Point Structs::Point::operator +(const int & number) const {
	return Structs::Point(_x + number, _y + number);
}

Structs::Point Structs::Point::operator -(const int & number) const {
	return Structs::Point(_x - number, _y - number);
}

Structs::Point Structs::Point::operator /(const int & number) const {
	return Structs::Point(_x / number, _y / number);
}

Structs::Point Structs::Point::operator /(double & number) const {
	return Structs::Point(ceil(_x / number), ceil(_y / number));
}

Structs::Point Structs::Point::operator *(const int & number) const {
	return Structs::Point(_x * number, _y * number);
}

void Structs::Point::operator =(const Structs::Point & point) {
	_x = point._x;
	_y = point._y;
}

Structs::Location::Location() {
	this->_x = 0;
	this->_y = 0;
	this->_yaw = 0;
}

Structs::Location::Location(double x, double y, double yaw) {
	this->_x = x;
	this->_y = y;
	this->_yaw = yaw;
}

Structs::Location::Location(Point p, double yaw) {
	this->_x = p.getX();
	this->_y = p.getY();
	this->_yaw = yaw;
}

double Structs::Location::getX() {
	return _x;
}

void Structs::Location::setX(double x) {
	_x = x;
}

double Structs::Location::getY() {
	return _y;
}

void Structs::Location::setY(double y) {
	_y = y;
}

double Structs::Location::getYaw() {
	return _yaw;
}

void Structs::Location::setYaw(double yaw) {
	_yaw = yaw;
}

Structs::Point Structs::Location::pointValue() {
	return Structs::Point(_x, _y);
}

string Structs::Location::toString() {
	return "(" + Helper::intToString((int) floor(_x)) + ", " +Helper::intToString((int) floor(_y)) + ", " + Helper::doubleToString(_yaw) + ")";
}

bool Structs::Location::operator ==(const Location & location) const {
	return (_x == location._x) && (_y == location._y) && (_yaw == location._yaw);
}

bool Structs::Location::operator !=(const Location & location) const {
	return (_x != location._x) || (_y != location._y) || (_yaw != location._yaw);
}

Structs::Location Structs::Location::operator +(const Location & location) const {
	return Location(_x + location._x, _y + location._y, _yaw + location._yaw);
}

Structs::Location Structs::Location::operator -(const Location & location) const {
	return Location(_x - location._x, _y - location._y, _yaw - location._yaw);
}

void Structs::Location::operator =(const Location & location) {
	_x = location._x;
	_y = location._y;
	_yaw = location._yaw;
}

Structs::Node::Node() {
	_point = Point();
	_g = 0;
	_h = 0;
	_turnFactor = 0;
	_wallFactor = 0;
}

Structs::Node::Node(Point p, double GGrade) {
	_point = p;
	_g = GGrade;
	_h = 0;
	_turnFactor = 0;
	_wallFactor = 0;
}

Structs::Point Structs::Node::getPoint() {
	return _point;
}

void Structs::Node::setPoint(Structs::Point point) {
	_point = point;
}

double Structs::Node::getG() {
	return _g;
}

void Structs::Node::setG(double g) {
	_g = g;
}

double Structs::Node::getH() {
	return _h;
}

double Structs::Node::getF() {
	return _g + _h;
}

double Structs::Node::getTurnFactor() {
	return _turnFactor;
}

void Structs::Node::setTurnFactor(double turnFactor) {
	_turnFactor = turnFactor;
}

double Structs::Node::getWallFactor() {
	return _wallFactor;
}

void Structs::Node::setWallFactor(double wallFactor) {
	_wallFactor = wallFactor;
}

void Structs::Node::calcHGrade(Point goal) {
	_h = _point.manhattanDistance(goal) * 2;
}

Structs::Size::Size() {
	this->_width = 0;
	this->_height = 0;
}

Structs::Size::Size(int width, int height) {
	this->_width = width;
	this->_height = height;
}

int Structs::Size::getWidth() {
	return _width;
}

void Structs::Size::setWidth(int width) {
	_width = width;
}

int Structs::Size::getHeight() {
	return _height;
}

void Structs::Size::setHeight(int height) {
	_height = height;
}

string Structs::Size::toString() {
	return "(" + Helper::intToString(_width) + ", " + Helper::intToString(_height) + ")";
}

bool Structs::Size::operator ==(const Size & size) const {
	return (_width == size._width) && (_height == size._height);
}

bool Structs::Size::operator !=(const Size & size) const {
	return (_width != size._width) || (_height != size._height);
}

Structs::Size Structs::Size::operator +(const Size & size) const {
	return Size(_width + size._width, _height + size._height);
}

Structs::Size Structs::Size::operator -(const Size & size) const {
	return Size(_width - size._width, _height - size._height);
}

void Structs::Size::operator =(const Size & size) {
	_width = size._width;
	_height = size._height;
}

Structs::ConfigurationProperty::ConfigurationProperty(string token, string value) {
	_token = token;
	_value = value;
}

string Structs::ConfigurationProperty::getToken() {
	return _token;
}

string Structs::ConfigurationProperty::getValue() {
	return _value;
}

void Structs::ConfigurationProperty::setValue(string value) {
	_value = value;
}
