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
private:
	PlayerClient *_playerClient;
	Position2dProxy * _position;
	LaserProxy * _laserProxy;

	vector<float> getLaserScan();

public:
	virtual ~Robot();
	Robot(char* ip, int port);

	Structs::Location getLocation();
	Structs::Point getPosition();
	void setRobotLocation(Structs::Location location);
	void setRobotPosition(Structs::Point position, float yaw);

	void Read();
	float getLaserDistance(int index);
	void setSpeed(float xSpeed, float angularSpeed);
};

#endif
