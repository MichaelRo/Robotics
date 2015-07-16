/*
 * TurnInPlace.cpp
 *
 *	Created on: Jun 25, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "TurnInPlace.h"

/**
	Destructs the TurnInPlace
*/
TurnInPlace::~TurnInPlace() {

}

/**
	Initializes a GoToPoint object

	@param robot - the access of the details about the robot will happen with this object.
	@param localizationManager - get information about the locations of the particles.
	@param neededYaw - the yaw the robot need to turn.
*/
TurnInPlace::TurnInPlace(Robot * robot, LocalizationManager * localizationManager, float neededYaw): Behavior(robot, localizationManager) {
	_neededYaw = neededYaw;
}

/**
	 The condition if the robot can start GoForward.

	 @return - true.
 */
bool TurnInPlace::startCondition() {
	return true;
}

/**
	 The condition if the robot need to turn more in order to arrive the wanted yaw.

	 @return - if the robot close enough to the yaw.
 */
bool TurnInPlace::stopCondition() {
//	float yaw = abs(_robot->getLocation().getYaw() - _neededYaw);
	float neededYawDelta = _neededYaw - _robot->getLocation().getYaw();
	cout << "neededYawDelta: " << Helper::floatToString(neededYawDelta) << " compromizedYaw: " << Helper::floatToString(COMPROMISED_YAW) << endl;

	if (neededYawDelta <= COMPROMISED_YAW) {
		return true;
	}

	return false;
}

/**
	This method set the yaw the robot need to turn.
 */
void TurnInPlace::behave() {
	int angularSpeedFactor = 1;

	if (abs(_robot->getLocation().getYaw() - _neededYaw) > abs(_robot->getLocation().getYaw() - (360 - _neededYaw))) {
		angularSpeedFactor = -1;
	}

	_robot->setSpeed((float) 0, (float) angularSpeedFactor * YAW_DELTA);
}
