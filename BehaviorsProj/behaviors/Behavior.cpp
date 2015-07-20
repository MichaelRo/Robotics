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
vector<Behavior*> Behavior::getBehaviors() {
    return _behaviors;
}

/**
	This method will make the robot do the current behavior.
	NOTE: remove the comments mark before adding LocalizationManager
 */
void Behavior::action() {
	Structs::Location locationBeforeAction = _robot->getOdometry();

	_robot->Read();

	behave();

 	_robot->Read();

	Structs::Location locationAfterAction = _robot->getOdometry();
	Structs::Location locationDelta = locationAfterAction - locationBeforeAction;

	_localizationManager->updateParticles(locationDelta, _robot->getLaserScan());

	// Maybe should be moved to update once per behavior?
	if (_localizationManager->getHighestBelief() >= Globals::BELIEF_THRESHOLD) {
		_robot->setRobotLocation(_localizationManager->getProbableLocation());
	} else {
		_robot->setRobotLocation(_robot->getOdometry());
	}
}
