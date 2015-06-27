/*
 * TurnRight.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: Itay Desalto
 */

#ifndef TURNINPLACE_H_
#define TURNINPLACE_H_

#include <iostream>
#include "Behavior.h"
#include "GoForward.h"
#include "../Robot.h"

class TurnInPlace: public Behavior
{
private:
    bool chooseDirection();
    bool _turnLeft;

public:
	TurnInPlace(Robot* robot);
	bool startCondition();
	bool stopCondition();
	void action();
	virtual ~TurnInPlace();
};

#endif
