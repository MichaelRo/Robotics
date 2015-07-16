/*
 * GoToPoint.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "GoToPoint.h"

/**
	Destructs the GoToPoint
*/
GoToPoint::~GoToPoint() {
	delete _turnInPlaceBehavior;
	delete _goForwardBehavior;
}

/**
	Initializes a GoToPoint object

	@param robot - the access of the details about the robot will happen with this object.
	@param localizationManager - get information about the locations of the particles.
	@param goalPoint - the point the robot supposed to arrived to.
	@param wantedYaw - the yaw the robot supposed to turn before GoForward.
*/
GoToPoint::GoToPoint(Robot * robot, LocalizationManager * localizationManager, Structs::Point goalPoint, float neededYaw) : Behavior(robot, localizationManager) {
	_goalPoint = goalPoint;
	_neededYaw = neededYaw;

	_turnInPlaceBehavior = new TurnInPlace(_robot, _localizationManager, _neededYaw);
	_goForwardBehavior = new GoForward(_robot, _localizationManager, goalPoint);

	initializeGoToPointBehavior();
}

/**
	This method initialize the yaw the robot need to turn, and the GoForward object.
 */
void GoToPoint::initializeGoToPointBehavior() {
	addNext(_turnInPlaceBehavior);
	addNext(_goForwardBehavior);
}

/**
	This method check if the robot end his route.

	@return - Is the robot arrive to the goal point?
 */
bool GoToPoint::isGoalLocationReached() {
	return _robot->getPosition().distanceBetweenPoints(_goalPoint) <= COMPROMISED_DISTANCE;
}

/**
	 The condition if the robot can start GoToPoint.

	 @return - true.
 */
bool GoToPoint::startCondition() {
	return true;
}

/**
	 The condition if the robot arrived to the wanted point.

	 @return - if the robot close enough.
 */
bool GoToPoint::stopCondition() {
	return isGoalLocationReached();
}

/**
	This method make the robot going to the goalPoint.
 */
void GoToPoint::behave() {
	vector<Behavior*> behaviors = getBehaviors();

	for (vector<Behavior*>::iterator behaviorsIterator = behaviors.begin(); behaviorsIterator != behaviors.end(); behaviorsIterator++) {
		Behavior * behavior = *(behaviorsIterator).operator ->();

		_robot->Read();

		if (behavior->startCondition()) {
			while (!behavior->stopCondition()) {
				behavior->action();
			}

			// Consider to implement a stop method
			_robot->setSpeed((float) 0, (float) 0);
		}
	}

	// What to do when the robot miss the point?
	if (!isGoalLocationReached()) {
		initializeGoToPointBehavior();

		action();
	}
}
