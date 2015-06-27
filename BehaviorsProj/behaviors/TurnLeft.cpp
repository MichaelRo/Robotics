/*
 * TurnRight.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: Itay Desalto
 */

#include "TurnLeft.h"
#include "../Helper.h"

TurnLeft::TurnLeft(Robot* robot):Behavior(robot)
{
}

bool TurnLeft::startCondition()
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

bool TurnLeft::stopCondition() {
	for (int i= Helper::DegreesToIndex(-120) ; i<(Helper::DegreesToIndex(-60)) ; i++)
		{
			if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
			{
				return true;
			}

		}
		return false;
}

void TurnLeft::action()
{
	_robot->setSpeed(0.0,1.0);
}

TurnLeft::~TurnLeft()
{
}
