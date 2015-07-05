/*
 * Robot.h
 *
 *  Created on: June 18, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "LocalizationManager.h"

#include <libplayerc++/playerc++.h>

#include <vector>

using namespace PlayerCc;
using namespace std;

class Robot {
	PlayerClient*_playerClient;
	Position2dProxy* _position;
	LaserProxy* _laserProxy;
	LocalizationManager* _localizationManager;

public:
	float getLaserDistance(int index);
	vector<float> getLaserScan();
	float getX();
	float getY();
	float getYaw();
	void setRobotPosition(Structs::Point position, float yaw);
	virtual ~Robot();

	Robot(char* ip, int port);

	void Read();

	void setSpeed(float xSpeed, float angularSpeed);
};

#endif
