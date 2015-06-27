/*
 * TurnRight.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: Itay Desalto
 */

#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include <iostream>
#include "Behavior.h"
#include "../Robot.h"

class TurnLeft: public Behavior
{
public:
	TurnLeft(Robot* robot);
	bool startCondition();
	bool stopCondition();
	void action();
	virtual ~TurnLeft();
};

#endif
