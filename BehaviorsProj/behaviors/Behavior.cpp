/*
 * Behavior.cpp
 *
 *	Created on: Jun 25, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Behavior.h"

Behavior::Behavior(Robot * robot) {
    _robot = robot;
}

/*
 * This method will add possible behavior that will that is possible to run after this one.
 */
void Behavior::addNext(Behavior * behavior) {
    _behaviors.push_back(behavior);
}

/*
 * This method returns the first possible behavior that the robot can use.
 *
 * Returns NULL if no behavior is available.
 */
Behavior * Behavior::getNext() {
    for (vector<Behavior*>::iterator it = _behaviors.begin(); it != _behaviors.end(); ++it) {
        if ((*it)->startCondition()) {
            return *it;
        }
    }

    return NULL;
}

Behavior::~Behavior() {
    _behaviors.clear();
}
