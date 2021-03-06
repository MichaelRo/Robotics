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
#include <cmath>
#include <libplayerc++/playerc++.h>

#include "../Localization/LocalizationManager.h"
#include "../Framework/Structs.h"
#include "../Utils/Helper.h"

using namespace PlayerCc;
using namespace std;

class Robot {
private:
	PlayerClient *_playerClient;
	Position2dProxy * _position;
	LaserProxy * _laserProxy;

	Structs::Location _location;

public:
	virtual ~Robot();
	Robot(char* ip, int port);

	Structs::Point getPosition();
	Structs::Location getLocation();
	Structs::Location getOdometry();
	Structs::Point getOdometryPoint();
	void setRobotLocation(Structs::Location location);
	void setOdometry(Structs::Location location);

	void setSpeed(double xSpeed, double angularSpeed);
	void Read();
	vector<double> getLaserScan();
	double getLaserDistance(int index);
};

#endif
