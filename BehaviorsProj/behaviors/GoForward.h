/*
 * GoForward.h
 *
 *	Created on: Jun 26, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include "Behavior.h"

#include <iostream>

using namespace std;

class GoForward: public Behavior {
private:
	static const int COMPROMISED_DISTANCE = 0.2;

public:
	GoForward(Robot * robot);
	virtual ~GoForward();

	bool startCondition();
	bool stopCondition();
	void action();
};

#endif
