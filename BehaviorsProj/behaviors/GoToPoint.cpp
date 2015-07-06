/*
 * GoToPoint.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "GoToPoint.h"

GoToPoint::~GoToPoint() {

}

GoToPoint::GoToPoint(Robot * robot, Structs::Point goalPoint, float wantedYaw) : Behavior(robot) {
	_goalPoint = goalPoint;
	_wantedYaw = wantedYaw;

	// Maybe we need to send (_wantedYaw - _robotLocation._yaw) ?
	_turnInPlaceBehavior = new TurnInPlace(robot, _wantedYaw);
	_goForwardBehavior = new GoForward(robot);

	addNext(_turnInPlaceBehavior);
	addNext(_goForwardBehavior);
}

bool GoToPoint::isGoalLocationReached() {
	return _robot->getLocation().pointValue().distanceBetweenPoints(_goalPoint) <= COMPROMISED_DISTANCE;
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
