/*
 * GoForward.cpp
 *
 *	Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "GoForward.h"
#include "../Helper.h"

GoForward::~GoForward() {

}

GoForward::GoForward(Robot * robot) : Behavior(robot) {

}

bool GoForward::startCondition() {
	return true;
}

bool GoForward::stopCondition() {
	for (int i = Helper::DegreesToIndex(-30); i < Helper::DegreesToIndex(30); i++) {
		if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE) {
			return true;
		}
	}

	return false;
}

void GoForward::action() {
	_robot->setSpeed(0.7, 0.0);
}
