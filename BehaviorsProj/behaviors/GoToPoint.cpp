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
GoToPoint::GoToPoint(Robot * robot, LocalizationManager * localizationManager, Structs::Point goalPoint) : Behavior(robot, localizationManager) {
	_goalPoint = goalPoint;

	initializeGoToPointBehavior();
}

/**
	Calculates the needed (non-relative) yaw to get from the robot's current location to a goal point

	@param goalPoint - the goal point
	@return - yaw in degrees
*/
float GoToPoint::calculateNeededYaw(Structs::Point goalPoint) {
//	_robot->Read();
	Structs::Point startPoint = _robot->getPosition();

	float yDeltaToPoint = abs(goalPoint.getY() - startPoint.getY());
	float distanceToPoint = startPoint.distanceBetweenPoints(goalPoint);

	return Helper::radiansToDegrees(abs(acos(yDeltaToPoint / distanceToPoint) - M_PI));
}

/**
	This method initialize the yaw the robot need to turn, and the GoForward object.
 */
void GoToPoint::initializeGoToPointBehavior() {
	_turnInPlaceBehavior = new TurnInPlace(_robot, _localizationManager, calculateNeededYaw(_goalPoint));
	_goForwardBehavior = new GoForward(_robot, _localizationManager, _goalPoint);

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
	vector<Behavior*>::iterator behaviorsIterator = behaviors.begin();

	// TurnInPlace behavior
	Behavior * turnInPlacebehavior = *(behaviorsIterator).operator ->();
	_robot->Read();

	if (turnInPlacebehavior->startCondition()) {
		while (!turnInPlacebehavior->stopCondition()) {
			turnInPlacebehavior->action();
		}

		// Consider to implement a stop method
		_robot->setSpeed((float) 0, (float) 0);
	}

	behaviorsIterator++;

	// GoForward behavior
	Behavior * goForwardBehavior = *(behaviorsIterator).operator ->();

	_robot->Read();

	if (goForwardBehavior->startCondition()) {
		int iterationIndex = 1;

		while (!goForwardBehavior->stopCondition()) {
			goForwardBehavior->action();

			if (iterationIndex++ > 10) {
				// IterationIndex reinitialization
				iterationIndex = 1;

				float neededYawDelta = calculateNeededYaw(_goalPoint) - _robot->getLocation().getYaw();
				cout << "neededYawDelta: " << Helper::floatToString(neededYawDelta) << " compromizedYaw: " << Helper::floatToString(COMPROMISED_YAW) << endl;

				if (neededYawDelta > COMPROMISED_YAW)
					break;
			}
		}

		// Consider to implement a stop method
		_robot->setSpeed((float) 0, (float) 0);
	}

	// Checking if the robot arrived to the goal location
	if (!isGoalLocationReached()) {
		initializeGoToPointBehavior();

		action();
	}
}
