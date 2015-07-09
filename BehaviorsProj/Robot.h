/*
 * Robot.h
 *
 *  Created on: June 18, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <vector>
#include <iostream>
#include <libplayerc++/playerc++.h>

#include "LocalizationManager.h"
#include "Structs.h"
#include "Helper.h"

using namespace PlayerCc;
using namespace std;

class Robot {
private:
	PlayerClient *_playerClient;
	Position2dProxy * _position;
	LaserProxy * _laserProxy;

public:
	virtual ~Robot();
	Robot(char* ip, int port);

	Structs::Location getLocation();
	Structs::Point getPosition();
	void setRobotLocation(Structs::Location location);

	void setSpeed(float xSpeed, float angularSpeed);
	void Read();
	vector<float> getLaserScan();
	float getLaserDistance(int index);
};

#endif
