/*
 * GoForward.cpp
 *
 *	Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "GoForward.h"

/**
	Destructs the GoForward
*/
GoForward::~GoForward() {

}

/**
	Initializes a GoForward object

	@param robot - the access of the details about the robot will happen with this object.
	@param localizationManager - get information about the locations of the particles.
	@param goalPoint - the point the robot supposed to arrived to.
*/
GoForward::GoForward(Robot * robot, LocalizationManager * localizationManager, Structs::Point goalPoint) : Behavior(robot, localizationManager) {
	_goalPoint = goalPoint;
}

/**
	 The condition if the robot can start GoForward.

	 @return - true.
 */
bool GoForward::startCondition() {
	return true;
}

/**
	 The condition if the robot need to stop GoForward.

	 @return - if the robot close enough or there is an obstacle in his way.
 */
bool GoForward::stopCondition() {
	if (_robot->getPosition().distanceBetweenPoints(_goalPoint) <= Globals::COMPROMISED_DISTANCE)
		return true;

	for (int i = Helper::degreesToIndex((Globals::TOTAL_DEGREES / 2) - 20); i < Helper::degreesToIndex((Globals::TOTAL_DEGREES / 2) + 20); i += Helper::degreesToIndex(3)) {
		if (_robot->getLaserDistance(i) < Globals::MINIMUM_DISTANCE_FROM_WALL) {
			return true;
		}
	}

	return false;
}

/**
	This method set the speed of the robot when GoForward.
 */
void GoForward::behave() {
	_robot->setSpeed((float) Globals::MOVEMENT_DELTA, 0);
}
