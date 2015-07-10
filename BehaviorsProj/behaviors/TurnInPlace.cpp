/*
 * TurnInPlace.cpp
 *
 *	Created on: Jun 25, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "TurnInPlace.h"

TurnInPlace::~TurnInPlace() {

}

TurnInPlace::TurnInPlace(Robot * robot, LocalizationManager * localizationManager, float neededYaw): Behavior(robot, localizationManager) {
	_neededYaw = neededYaw;
}

bool TurnInPlace::startCondition() {
	return true;
}

bool TurnInPlace::stopCondition() {
	float yawww = abs(_robot->getLocation()._yaw - ((_neededYaw * 180) / M_PI));
	cout << "(currentYaw - neededYaw): " << Helper::floatToString(yawww) << " compromizedYaw: " << Helper::floatToString(COMPROMISED_YAW) << endl;

	if (yawww <= COMPROMISED_YAW) {
		return true;
	}

	return false;
}

void TurnInPlace::behave() {
	int angularSpeedFactor = 1;

	float realYaw = _robot->getLocation()._yaw;
	float realNeeded = (_neededYaw * 180) / M_PI;

	if (abs(realYaw - realNeeded) > abs(realYaw - (360 - realNeeded))) {
		angularSpeedFactor = -1;
	}

	_robot->setSpeed((float) 0, (float) angularSpeedFactor * YAW_DELTA);
}
