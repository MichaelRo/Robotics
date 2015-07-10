/*
 * GoForward.cpp
 *
 *	Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "GoForward.h"

GoForward::~GoForward() {

}

GoForward::GoForward(Robot * robot, LocalizationManager * localizationManager, Structs::Point goalPoint) : Behavior(robot, localizationManager) {
	_goalPoint = goalPoint;
}

bool GoForward::startCondition() {
	return true;
}

bool GoForward::stopCondition() {
	if (_robot->getPosition().realPointToRobotPoint().distanceBetweenPoints(_goalPoint) <= COMPROMISED_DISTANCE)
		return true;

	for (int i = Helper::DegreesToIndex(-30); i < Helper::DegreesToIndex(30); i++) {
		if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE) {
			cout << "Stopped going forward because of an obstacle" << endl;

			return true;
		}
	}

	return false;
}

void GoForward::behave() {
	_robot->setSpeed((float) 0.5, (float) 0);

	cout << "Going forward" << endl;
}
