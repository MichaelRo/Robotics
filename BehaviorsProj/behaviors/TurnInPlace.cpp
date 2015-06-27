/*
 * TurnRight.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: Itay Desalto
 */

#include "TurnInPlace.h"
#include "../Helper.h"

TurnInPlace::TurnInPlace(Robot* robot):Behavior(robot)
{
	_turnLeft = true;
}

bool TurnInPlace::startCondition()
{
	_turnLeft = chooseDirection();

	return true;
}

bool TurnInPlace::stopCondition()
{
    int freePointsCount = 0;

    // Count how many of the "forward" path is clear.
    for (int i = Helper::DegreesToIndex(-30); i < Helper::DegreesToIndex(30); i = i + 3) {
        if (_robot->getLaserDistance(i) > Helper::MINIMUM_WALL_RANGE) {
            freePointsCount++;

            // If e counted at least 20 clear paths (based on the angles) we can stop turning
            // and go forward
            if (freePointsCount >= 20) {
                return true;
            }
        }
    }

    return false;
}

bool TurnInPlace::chooseDirection() {
    int LeftWallNearByCount = 0;
    int RightWallNearByCount = 0;

    // Count the number of walls in the left and in the right.
    for (int i = Helper::DegreesToIndex(-10); i < Helper::DegreesToIndex(10); i++) {
        if (_robot->getLaserDistance(Helper::DegreesToIndex(150) + i) < Helper::MINIMUM_WALL_RANGE
                || _robot->getLaserDistance(Helper::DegreesToIndex(210) + i) < Helper::MINIMUM_WALL_RANGE)
            LeftWallNearByCount++;
        if (_robot->getLaserDistance(Helper::DegreesToIndex(90) + i) < Helper::MINIMUM_WALL_RANGE
                || _robot->getLaserDistance(Helper::DegreesToIndex(30) + i) < Helper::MINIMUM_WALL_RANGE)
            RightWallNearByCount++;
    }

    // Turn left if we have more walls on the right than in the left.
    return (RightWallNearByCount > LeftWallNearByCount);

}

void TurnInPlace::action()
{
	if (_turnLeft)
		_robot->setSpeed(0.0, 0.8);
	else
		_robot->setSpeed(0.0, -0.8);
}

TurnInPlace::~TurnInPlace()
{
}
