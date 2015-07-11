/*
 * Behavior.cpp
 *
 *	Created on: Jun 25, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Behavior.h"

/**
	Destructs behavior.
*/
Behavior::~Behavior() {
    _behaviors.clear();
}

/**
	Initializes a new Behavior.

	@param robot - the access of the details about the robot will happen with this object.
	@param localizationManager - get information about the locations of the particles.
*/
Behavior::Behavior(Robot * robot, LocalizationManager * localizationManager) {
    _robot = robot;
    _localizationManager = localizationManager;
}

/**
	This method will add possible behavior that will that is possible to run after this one.

	@param behavior - this behavior will be added to the list of the behaviors that the robot will do.
*/
void Behavior::addNext(Behavior * behavior) {
    _behaviors.push_back(behavior);
}

/**
	This method returns the first possible behavior that the robot can use.

	@return - the behaviors and NULL if no behavior is available.
*/
// Maybe think about nice getNext() method?
vector<Behavior*> Behavior::getBehaviors() {
    return _behaviors;
}

/**
	This method will make the robot do the current behavior.
 */
void Behavior::action() {
	Structs::Location locationBeforeAction = _robot->getLocation();

	behave();

	Structs::Location locationAfterAction = _robot->getLocation();
	Structs::Location locationDelta = locationAfterAction - locationBeforeAction;

	_localizationManager->updateParticles(locationDelta, _robot->getLaserScan());

//	if (_localizationManager->getHighestBelief() >= LocalizationManager::BELIEF_THRESHOLD) {
//		cout << "Highest belief: " << _localizationManager->getHighestBelief() << endl;
//
//		// What if all the beliefs are 0? the robot will get a false location?
//		_robot->setRobotLocation(_localizationManager->getProbableLocation());
//	}
}
