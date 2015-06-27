/*
 * TurnRight.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: Itay Desalto
 */

#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include <iostream>
#include "Behavior.h"
#include "../Robot.h"

class GoForward: public Behavior
{
public:
	GoForward(Robot* robot);
	bool startCondition();
	bool stopCondition();
	void action();
	virtual ~GoForward();
};

#endif
