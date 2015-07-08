/*
 * GoToPoint.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "GoToPoint.h"

GoToPoint::~GoToPoint() {
	delete _turnInPlaceBehavior;
	delete _goForwardBehavior;
}

GoToPoint::GoToPoint(Robot * robot, LocalizationManager * localizationManager, Structs::Point goalPoint, float wantedYaw) : Behavior(robot, localizationManager) {
	_goalPoint = goalPoint;
	_wantedYaw = wantedYaw;

	// Maybe we need to send (_wantedYaw - _robotLocation._yaw) ?
	_turnInPlaceBehavior = new TurnInPlace(robot, localizationManager, _wantedYaw);
	_goForwardBehavior = new GoForward(robot, localizationManager);

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

void GoToPoint::behave() {
	vector<Behavior*> behaviors = getBehaviors();

	for (vector<Behavior*>::iterator behaviorsIterator = behaviors.begin(); behaviorsIterator != behaviors.end(); behaviorsIterator++) {
		Behavior * behavior = *(behaviorsIterator).operator ->();

		if (behavior->startCondition()) {
			while (!behavior->stopCondition()) {
				behavior->action();
			}

			// Consider to implement a stop method
			_robot->setSpeed((float) 0, (float) 0);
		}
	}
}
