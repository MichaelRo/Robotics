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
	_iterationNumber = 0;
}

/**
	Initializes a GoToPoint object

	@param robot - the access of the details about the robot will happen with this object.
	@param localizationManager - get information about the locations of the particles.
	@param neededYaw - the yaw the robot need to turn.
*/
TurnInPlace::TurnInPlace(Robot * robot, LocalizationManager * localizationManager, double neededYaw): Behavior(robot, localizationManager) {
	_iterationNumber = 0;
	_neededYaw = neededYaw;
}

bool TurnInPlace::startCondition() {
	++_iterationNumber;

	return true;
}

/**
	 The condition if the robot need to turn more in order to arrive the wanted yaw.

	 @return - if the robot close enough to the yaw.
 */
bool TurnInPlace::stopCondition() {
	double neededYawDelta = _neededYaw - _robot->getLocation().getYaw();

	double currentCompromizedYaw = (_iterationNumber == 1) ? Globals::COMPROMISED_YAW : (double) (Globals::COMPROMISED_YAW / 1.75);

	if (((neededYawDelta >= 0) && (neededYawDelta <= currentCompromizedYaw)) ||
		((neededYawDelta < 0) && (neededYawDelta >= (-1 * currentCompromizedYaw)))) {
		return true;
	}

	return false;
}

/**
	This method make the robot turn to the wanted yaw.
 */
void TurnInPlace::behave() {
	int angularSpeedFactor = 1;

	if (_neededYaw - _robot->getLocation().getYaw() < 0)
		angularSpeedFactor = -1;
	if (_neededYaw - _robot->getLocation().getYaw() < 10)
		_robot->setSpeed(0, (double) angularSpeedFactor * (Globals::YAW_TURN_DELTA / 2));
	else
		_robot->setSpeed(0, (double) angularSpeedFactor * Globals::YAW_TURN_DELTA);
}
