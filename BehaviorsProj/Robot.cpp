/*
 * Robot.cpp
 *
 *  Created on: June 18, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Robot.h"
#include "Helper.h"

Robot::Robot(char* ip, int port) {
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);
	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		Read();
}

float Robot::getLaserDistance(int index) {
	return _lp->GetRange(index);
}

vector<float> Robot::getLaserScan() {
	vector<float> laserScan;

	for (int i = 0; i <= Helper::DEGREES; i++) {
		laserScan.push_back(getLaserDistance(Helper::DegreesToIndex(i)));
	}

	return laserScan;
}

float Robot::getX() {
	return _pp->GetXPos();
}

float Robot::getY() {
	return _pp->GetYPos();
}

float Robot::getYaw() {
	return _pp->GetYaw();
}

void Robot::setSpeed(float xSpeed, float angularSpeed) {
	_pp->SetSpeed(xSpeed, angularSpeed);
}

void Robot::Read() {
	_pc->Read();
}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}
