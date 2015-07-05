/*
 * GoToPoint.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "GoToPoint.h"

GoToPoint::~GoToPoint() {
	delete _robotLocation;
	delete _goalLocation;
}

GoToPoint::GoToPoint(Robot * robot, Structs::Location * robotLocation, Structs::Location * goalLocation) : Behavior(robot) {
	_robotLocation = robotLocation;
	_goalLocation = goalLocation;

	_turnInPlaceBehavior = new TurnInPlace(robot);
	_goForwardBehavior = new GoForward(robot);

	addNext(_turnInPlaceBehavior);
}

bool GoToPoint::isGoalLocationReached() {
	return _robotLocation->pointValue().distanceBetweenPoints(_goalLocation->pointValue()) <= COMPROMISED_DISTANCE;
}

bool GoToPoint::startCondition() {
	return true;
}

bool GoToPoint::stopCondition() {
	return isGoalLocationReached();
}

void GoToPoint::action() {
	Behavior * behavior;

	while ((behavior = getNext()) != NULL) {
		while (!behavior->stopCondition()) {
			behavior->action();
		}
	}
}
