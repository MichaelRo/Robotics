/*
 * TurnRight.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: Itay Desalto
 */

#include "GoForward.h"
#include "../Helper.h"

GoForward::GoForward(Robot* robot) : Behavior(robot)
{
}

bool GoForward::startCondition()
{
	return true;
}

bool GoForward::stopCondition()
{
	for (int i= Helper::DegreesToIndex(-30) ; i < Helper::DegreesToIndex(30) ; i++)
	{
		if (_robot->getLaserDistance(i) < Helper::MINIMUM_WALL_RANGE)
		{
			return true;
		}
	}
	return false;
}

void GoForward::action()
{
	_robot->setSpeed(0.8, 0.0);
}

GoForward::~GoForward()
{
}
