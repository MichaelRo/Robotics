/*
 * TurnInPlace.h
 *
 *	Created on: Jun 25, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef TURNINPLACE_H_
#define TURNINPLACE_H_

#include "Behavior.h"
#include "GoForward.h"

#include <iostream>
#include <cmath>

using namespace std;

class TurnInPlace: public Behavior {
private:
	static const int COMPROMISED_YAW = 0.2;
	static constexpr float YAW_DELTA = 0.1;

	float _yaw;
	float _neededYaw;

	bool chooseDirection();

public:
	TurnInPlace(Robot * robot, float yaw);
	virtual ~TurnInPlace();

	bool startCondition();
	bool stopCondition();
	void action();
};

#endif
