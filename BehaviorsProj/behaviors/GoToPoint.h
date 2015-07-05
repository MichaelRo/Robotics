/*
 * GoToPoint.h
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef GOTOPOINT_H_
#define GOTOPOINT_H_

#include <cmath>

#include "Behavior.h"
#include "TurnInPlace.h"
#include "GoForward.h"
#include "../Structs.h"

using namespace std;

class GoToPoint: public Behavior {
private:
	static const int COMPROMISED_DISTANCE = 0.2;

	Structs::Location _robotLocation;
	Structs::Point _goalPoint;
	float _wantedYaw;

	TurnInPlace * _turnInPlaceBehavior;
	GoForward * _goForwardBehavior;

    float calculateWantedYaw(Structs::Point startPoint, Structs::Point goalPoint);
    bool isGoalLocationReached();

public:
	GoToPoint(Robot * robot, Structs::Point goalPoint);
	virtual ~GoToPoint();

	bool startCondition();
	bool stopCondition();
	void action();
};

#endif
