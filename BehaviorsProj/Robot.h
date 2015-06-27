/*
 * Robot.h
 *
 *  Created on: June 18, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>

using namespace PlayerCc;
class Robot {
	PlayerClient*_pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;

public:
	float getLaserDistance(int index);
	virtual ~Robot();

	Robot(char* ip, int port);

	void Read() {
		_pc->Read();
	}

	void setSpeed(float xSpeed, float angularSpeed) {
		_pp->SetSpeed(xSpeed, angularSpeed);
	}

	bool isRightFree() {
		if ((*_lp)[50] > 0.5)
			return true;
		else
			return false;
	}

	bool isForwardFree() {
		if ((*_lp)[332] > 0.5)
			return true;
		else
			return false;
	}
};

#endif
