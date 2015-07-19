/*
 * MovementManager.h
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef MOVEMENTMANAGER_H_
#define MOVEMENTMANAGER_H_

#include <list>

#include "Robot.h"
#include "../Framework/Structs.h"
#include "../PathPlanning/WaypointsManager.h"
#include "../Localization/LocalizationManager.h"
#include "../behaviors/GoToPoint.h"

using namespace std;

class MovementManager {
private:
	Robot * _robot;
	LocalizationManager * _localizationManager;
	list<Structs::Point> _wayPoints;

public:
	MovementManager(Robot * robot, LocalizationManager * localizationManager, WaypointsManager * _waypointsManager);
	virtual ~MovementManager();

	void start();
};

#endif
