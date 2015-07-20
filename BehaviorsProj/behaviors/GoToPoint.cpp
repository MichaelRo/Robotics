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
	Calculates the needed (non-relative) yaw to get from the robot's current location to the goal point

	@return - yaw in degrees
*/
float GoToPoint::calculateNeededYaw() {
	_robot->Read();

	Structs::Point startPoint = _robot->getPosition();

	float yDeltaToPoint = abs(_goalPoint.getY() - startPoint.getY());
	float distanceToPoint = startPoint.distanceBetweenPoints(_goalPoint);
	float neededYaw = acos(yDeltaToPoint / distanceToPoint);

	switch(getQuarter(startPoint)) {
		case Globals::Quarter::FIRST:
			return Helper::radiansToDegrees(M_PI_2 - neededYaw);
		case Globals::Quarter::SECOND:
			return Helper::radiansToDegrees(M_PI - neededYaw);
		case Globals::Quarter::THIRD:
			return Helper::radiansToDegrees(M_PI + M_PI_2 - neededYaw);
		case Globals::Quarter::FOURTH:
			return Helper::radiansToDegrees(M_PI * 2 - neededYaw);
		default:
			return neededYaw;
    }
}

/**
	This method initialize the yaw the robot need to turn, and the GoForward object.
 */
void GoToPoint::initializeGoToPointBehavior() {
	_turnInPlaceBehavior = new TurnInPlace(_robot, _localizationManager, calculateNeededYaw());
	_goForwardBehavior = new GoForward(_robot, _localizationManager, _goalPoint);

	addNext(_turnInPlaceBehavior);
	addNext(_goForwardBehavior);
}

/**
	This method check if the robot end his route.

	@return - Is the robot arrive to the goal point?
 */
bool GoToPoint::isGoalLocationReached() {
	return _robot->getPosition().distanceBetweenPoints(_goalPoint) <= Globals::COMPROMISED_DISTANCE;
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
		int checkYawDirectionIndex = 1;

		while (!goForwardBehavior->stopCondition()) {
			goForwardBehavior->action();

			if (checkYawDirectionIndex++ % 10 == 0) {
				float neededYawDelta = calculateNeededYaw() - _robot->getLocation().getYaw();

				if (((neededYawDelta >= 0) && (neededYawDelta > Globals::COMPROMISED_YAW)) ||
					((neededYawDelta < 0) && (neededYawDelta < (-1 * Globals::COMPROMISED_YAW))))
					break;
			}
		}

		// Consider to implement a stop method
		_robot->setSpeed(0, 0);
	}

	if (!isGoalLocationReached()) {
		// Adding reverse factor
		if (isLeftSideBlocked())
			for (int i = 0; i < 15; i++)
				_robot->setSpeed((float) ((-1) * 10), (float) (Globals::YAW_TURN_DELTA) * 10);
		else if (isRightSideBlocked())
			for (int i = 0; i < 15; i++)
				_robot->setSpeed((float) ((-1) * 10), (float) ((-1) * Globals::YAW_TURN_DELTA * 10));

		_robot->setSpeed(0, 0);

		initializeGoToPointBehavior();

		action();
	}
}

int GoToPoint::getQuarter(Structs::Point startPoint) {
	if (startPoint.getY() > _goalPoint.getY()) {
		if (startPoint.getX() > _goalPoint.getX())
			return Globals::Quarter::SECOND;
		else
			return Globals::Quarter::FIRST;
	} else {
		if (startPoint.getX() > _goalPoint.getX())
			return Globals::Quarter::THIRD;
		else
			return Globals::Quarter::FOURTH;
	}
}

bool GoToPoint::isLeftSideBlocked() {
	for (int i = Helper::degreesToIndex((Globals::TOTAL_DEGREES / 2) - 30); i < Helper::degreesToIndex(Globals::TOTAL_DEGREES / 2); i += Helper::degreesToIndex(3)) {
		if (_robot->getLaserDistance(i) < Globals::MINIMUM_DISTANCE_FROM_WALL) {
			return true;
		}
	}

	return false;
}

bool GoToPoint::isRightSideBlocked() {
	for (int i = Helper::degreesToIndex(Globals::TOTAL_DEGREES / 2); i < Helper::degreesToIndex((Globals::TOTAL_DEGREES / 2) + 30); i += Helper::degreesToIndex(3)) {
		if (_robot->getLaserDistance(i) < Globals::MINIMUM_DISTANCE_FROM_WALL) {
			return true;
		}
	}

	return false;
}
