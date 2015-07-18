/*
 * Behavior.h
 *
 *	Created on: Jun 25, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "../Robot.h"
#include "../LocalizationManager.h"
#include "../Structs.h"

#include <string>
#include <sstream>
#include <vector>

using namespace std;

//Class which handles the robot's behavior system control
class Behavior {
protected:
	Robot * _robot;
	LocalizationManager * _localizationManager;

	virtual void behave() = 0;

private:
    vector<Behavior*> _behaviors;

public:
    Behavior(Robot * robot, LocalizationManager * localizationManager);
    virtual ~Behavior();

    virtual bool startCondition() = 0;
    virtual bool stopCondition() = 0;

    void action();
    void addNext(Behavior * behavior);
    vector<Behavior*> getBehaviors();
};

#endif
