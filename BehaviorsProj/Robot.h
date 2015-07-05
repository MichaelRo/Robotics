/*
 * Robot.h
 *
 *  Created on: June 18, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <vector>

#include <libplayerc++/playerc++.h>

#include "LocalizationManager.h"
#include "Structs.h"

using namespace PlayerCc;
using namespace std;

class Robot {
	PlayerClient*_playerClient;
	Position2dProxy* _position;
	LaserProxy* _laserProxy;
	LocalizationManager* _localizationManager;

public:
	virtual ~Robot();
	Robot(char* ip, int port);

	float getLaserDistance(int index);
	vector<float> getLaserScan();
	Structs::Location getLocation();
	float getX();
	float getY();
	float getYaw();
	void setRobotPosition(Structs::Point position, float yaw);
	void Read();
	void setSpeed(float xSpeed, float angularSpeed);
};

#endif
