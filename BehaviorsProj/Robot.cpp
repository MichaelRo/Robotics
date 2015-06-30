/*
 * Robot.cpp
 *
 *  Created on: June 18, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Robot.h"
#include "Helper.h"

Robot::Robot(char* ip, int port) {
	_playerClient = new PlayerClient(ip,port);
	_position = new Position2dProxy(_playerClient);
	_laserProxy = new LaserProxy(_playerClient);

	_position->SetMotorEnable(true);
	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		Read();
}

float Robot::getLaserDistance(int index) {
	return _laserProxy->GetRange(index);
}

vector<float> Robot::getLaserScan() {
	vector<float> laserScan;

	for (int i = 0; i <= Helper::DEGREES; i++) {
		laserScan.push_back(getLaserDistance(Helper::DegreesToIndex(i)));
	}

	return laserScan;
}

float Robot::getX() {
	return _position->GetXPos();
}

float Robot::getY() {
	return _position->GetYPos();
}

float Robot::getYaw() {
	return _position->GetYaw();
}

void Robot::setSpeed(float xSpeed, float angularSpeed) {
	_position->SetSpeed(xSpeed, angularSpeed);
}

void Robot::Read() {
	_playerClient->Read();
}

Robot::~Robot() {
	delete _playerClient;
	delete _position;
	delete _laserProxy;
}
