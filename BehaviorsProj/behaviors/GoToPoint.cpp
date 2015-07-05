/*
 * GoToPoint.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "GoToPoint.h"

GoToPoint::~GoToPoint() {

}

GoToPoint::GoToPoint(Robot * robot, Structs::Point goalPoint) : Behavior(robot) {
	_robotLocation = robot->getLocation();
	_goalPoint = goalPoint;
	_wantedYaw = calculateWantedYaw(_robotLocation.pointValue(), _goalPoint);

	// Maybe we need to send (_wantedYaw - _robotLocation._yaw) ?
	_turnInPlaceBehavior = new TurnInPlace(robot, _wantedYaw);
	_goForwardBehavior = new GoForward(robot);

	addNext(_turnInPlaceBehavior);
	addNext(_goForwardBehavior);
}

float GoToPoint::calculateWantedYaw(Structs::Point startPoint, Structs::Point goalPoint) {
	return acosf((goalPoint._x - startPoint._x) * startPoint.distanceBetweenPoints(goalPoint));
}

bool GoToPoint::isGoalLocationReached() {
	return _robotLocation.pointValue().distanceBetweenPoints(_goalPoint) <= COMPROMISED_DISTANCE;
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
