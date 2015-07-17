/*
 * GoForward.h
 *
 *	Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include "Behavior.h"
#include "../Helper.h"

#include <iostream>

using namespace std;

class GoForward: public Behavior {
private:
	Structs::Point _goalPoint;

public:
	GoForward(Robot * robot, LocalizationManager * localizationManager, Structs::Point goalPoint);
	virtual ~GoForward();

	bool startCondition();
	bool stopCondition();
	void behave();
};

#endif
