/*
 * GoToPoint.h
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef GOTOPOINT_H_
#define GOTOPOINT_H_

#include "Behavior.h"
#include "TurnInPlace.h"
#include "GoForward.h"
#include "../Structs.h"

using namespace std;

class GoToPoint: public Behavior {
private:
	static const int COMPROMISED_DISTANCE = 0.2;

	Structs::Location * _robotLocation;
	Structs::Location * _goalLocation;
	TurnInPlace * _turnInPlaceBehavior;
	GoForward * _goForwardBehavior;

    bool isGoalLocationReached();

public:
	GoToPoint(Robot * robot, Structs::Location * robotLocation, Structs::Location * goalLocation);
	virtual ~GoToPoint();

	bool startCondition();
	bool stopCondition();
	void action();
};

#endif
