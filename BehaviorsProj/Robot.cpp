/*
 * Robot.cpp
 *
 *  Created on: June 18, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Robot.h"
#include "Helper.h"

Robot::~Robot() {
	delete _playerClient;
	delete _position;
	delete _laserProxy;
}

Robot::Robot(char * ip, int port) {
	_playerClient = new PlayerClient(ip,port);
	_position = new Position2dProxy(_playerClient);
	_laserProxy = new LaserProxy(_playerClient);

	_position->SetMotorEnable(true);
	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		Read();
}

Structs::Location Robot::getLocation() {
	return Structs::Location(_position->GetXPos(), _position->GetYPos(), _position->GetYaw());
}

Structs::Point Robot::getPosition() {
	return Structs::Point(_position->GetXPos(), _position->GetYPos());
}

void Robot::setRobotPosition(Structs::Point position, float yaw) {
	_position->SetOdometry(position._x, position._y, yaw);
}

void Robot::setSpeed(float xSpeed, float angularSpeed) {
	_position->SetSpeed(xSpeed, angularSpeed);
}

void Robot::Read() {
	_playerClient->Read();
}

vector<float> Robot::getLaserScan() {
	vector<float> laserScan;

	for (int i = 0; i <= Helper::DEGREES; i++) {
		laserScan.push_back(getLaserDistance(Helper::DegreesToIndex(i)));
	}

	return laserScan;
}

float Robot::getLaserDistance(int index) {
	return _laserProxy->GetRange(index);
}
