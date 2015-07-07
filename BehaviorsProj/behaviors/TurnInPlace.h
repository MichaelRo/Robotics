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
	static constexpr float COMPROMISED_YAW = 1.0;
	static constexpr float YAW_DELTA = 0.2;

	float _neededYaw;

	bool chooseDirection();

public:
	TurnInPlace(Robot * robot, LocalizationManager * localizationManager, float neededYaw);
	virtual ~TurnInPlace();

	bool startCondition();
	bool stopCondition();
	void behave();
};

#endif
