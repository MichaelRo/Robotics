/*
 * TurnRight.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "TurnRight.h"
#include "../Helper.h"

TurnRight::TurnRight(Robot* robot):Behavior(robot) {

}

bool TurnRight::startCondition()
{
	for (int i = Helper::DegreesToIndex(-30); i< Helper::DegreesToIndex(0); i++)
	{
		if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
		{
			for (int j = Helper::DegreesToIndex(0); j < Helper::DegreesToIndex(30); j++)
			{
				if (_robot->getLaserDistance(j) > (Helper::MINIMUM_WALL_RANGE))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool TurnRight::stopCondition() {
	for (int i= Helper::DegreesToIndex(60) ; i<(Helper::DegreesToIndex(120)) ; i++)
		{
			if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
			{
				return true;
			}

		}
		return false;
}

void TurnRight::action()
{
	_robot->setSpeed(0.0,-1.0);
}

TurnRight::~TurnRight()
{
}
