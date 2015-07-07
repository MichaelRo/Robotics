/*
 * TurnInPlace.cpp
 *
 *	Created on: Jun 25, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "TurnInPlace.h"
#include "../Helper.h"

TurnInPlace::~TurnInPlace() {

}

TurnInPlace::TurnInPlace(Robot * robot, LocalizationManager * localizationManager, float neededYaw): Behavior(robot, localizationManager) {
	_neededYaw = neededYaw;
}

bool TurnInPlace::startCondition() {
	return true;
}

bool TurnInPlace::stopCondition() {
	// Just for debugging
	float yawww = _robot->getLocation()._yaw;

	if (abs(_robot->getLocation()._yaw - _neededYaw) <= COMPROMISED_YAW) {
//		int freePointsCount = 0;
//
//		// Count how many of the "forward" path is clear.
//		for (int i = Helper::DegreesToIndex(-30); i < Helper::DegreesToIndex(30); i = i + 3) {
//			if (_robot->getLaserDistance(i) > Helper::MINIMUM_WALL_RANGE) {
//				// If e counted at least 20 clear paths (based on the angles) we can stop turning
//				// and go forward
//				if (++freePointsCount >= 20) {
//					return true;
//				}
//			}
//		}

		return true;
	}

	return false;
}

void TurnInPlace::behave() {
	int angularSpeedFactor = (_robot->getLocation()._yaw > _neededYaw) ? -1 : 1;
	float angularSpeed = angularSpeedFactor * YAW_DELTA;

	_robot->setSpeed(0.0, angularSpeed);
}
