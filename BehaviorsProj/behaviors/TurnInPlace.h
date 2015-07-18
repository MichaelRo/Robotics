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
	float _neededYaw;
	int _iterationNumber;

	bool chooseDirection();

public:
	TurnInPlace(Robot * robot, LocalizationManager * localizationManager, float neededYaw);
	virtual ~TurnInPlace();

	bool startCondition();
	bool stopCondition();
	void behave();
};

#endif
