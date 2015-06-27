/*
 * behavior.h
 *
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "../Robot.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

//Class which handles the robot's behavior system control
class Behavior {

protected:
    Robot* _robot;

private:
    vector<Behavior*> _behaviors;

public:
    Behavior(Robot*);
    virtual ~Behavior();
    virtual bool startCondition() = 0;
    virtual bool stopCondition() = 0;
    virtual void action() = 0;
    void addNext(Behavior*);
    Behavior* getNext();
    virtual string getName() = 0;

};

#endif
