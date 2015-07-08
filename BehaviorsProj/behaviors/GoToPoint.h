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
	static constexpr float COMPROMISED_DISTANCE = 0.4;

	Structs::Point _goalPoint;
	float _wantedYaw;

	TurnInPlace * _turnInPlaceBehavior;
	GoForward * _goForwardBehavior;

    bool isGoalLocationReached();
    void initializeGoToPointBehavior();

public:
	GoToPoint(Robot * robot, LocalizationManager * localizationManager, Structs::Point goalPoint, float wantedYaw);
	virtual ~GoToPoint();

	bool startCondition();
	bool stopCondition();
	void behave();
};

#endif
