/*
 * GoToPoint.cpp
 *
 *  Created on: Jul 5, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "GoToPoint.h"

/**
	Destructs the GoToPoint
*/
GoToPoint::~GoToPoint() {
	delete _turnInPlaceBehavior;
	delete _goForwardBehavior;
}

/**
	Initializes a GoToPoint object

	@param robot - the access of the details about the robot will happen with this object.
	@param localizationManager - get information about the locations of the particles.
	@param goalPoint - the point the robot supposed to arrived to.
	@param wantedYaw - the yaw the robot supposed to turn before GoForward.
*/
GoToPoint::GoToPoint(Robot * robot, LocalizationManager * localizationManager, Structs::Point goalPoint) : Behavior(robot, localizationManager) {
	_goalPoint = goalPoint;

	initializeGoToPointBehavior();
}

Structs::Point GoToPoint::getClosestRoutePoint(Structs::Point currentPoint) {
	list<int> neighborsValues = list<int>();
//	neighborsValues.push_back(Map::FREE_CELL);
//	neighborsValues.push_back(Map::ROUTE_CELL);
	neighborsValues.push_back(0);
	neighborsValues.push_back(5);
//	neighborsValues.push_back(Map::PADDING_CELL);

	list<Structs::Point> neighbors = _localizationManager->getMap()->getCellsNeighborsByValue(currentPoint, neighborsValues, _localizationManager->getMap()->getMapResolution());
	neighbors.sort();

	// Running twice - first searching for route cells, second - searching for their neighbors
	for (int iteration = 0; iteration < 2; iteration++) {
		for (list<Structs::Point>::iterator neighborsIterator = neighbors.begin(); neighborsIterator != neighbors.end(); neighborsIterator++) {
			Structs::Point currentNeighbor = *neighborsIterator.operator ->();

			if (_localizationManager->getMap()->getCellValue(currentNeighbor, _localizationManager->getMap()->getMapResolution()) == Map::ROUTE_CELL)
				return *neighborsIterator.operator ->();
			else if (iteration >= 1)
				// Need to add a limit!!!!
				return getClosestRoutePoint(currentNeighbor);
		}
	}

	return Structs::Point(0,0);
}

/**
	Calculates the needed (non-relative) yaw to get from the robot's current location to the goal point

	@return - yaw in degrees
*/
float GoToPoint::calculateNeededYaw() {
	_robot->Read();

	Structs::Point startPoint = _robot->getPosition();

	float yDeltaToPoint = abs(_goalPoint.getY() - startPoint.getY());
	float distanceToPoint = startPoint.distanceBetweenPoints(_goalPoint);

	return Helper::radiansToDegrees(abs(acos(yDeltaToPoint / distanceToPoint) - M_PI));
}

/**
	This method initialize the yaw the robot need to turn, and the GoForward object.
 */
void GoToPoint::initializeGoToPointBehavior() {
	_turnInPlaceBehavior = new TurnInPlace(_robot, _localizationManager, calculateNeededYaw());
	_goForwardBehavior = new GoForward(_robot, _localizationManager, _goalPoint);

	addNext(_turnInPlaceBehavior);
	addNext(_goForwardBehavior);
}

/**
	This method check if the robot end his route.

	@return - Is the robot arrive to the goal point?
 */
bool GoToPoint::isGoalLocationReached() {
	return _robot->getPosition().distanceBetweenPoints(_goalPoint) <= Helper::COMPROMISED_DISTANCE;
}

/**
	 The condition if the robot can start GoToPoint.

	 @return - true.
 */
bool GoToPoint::startCondition() {
	return true;
}

/**
	 The condition if the robot arrived to the wanted point.

	 @return - if the robot close enough.
 */
bool GoToPoint::stopCondition() {
	return isGoalLocationReached();
}

/**
	This method make the robot going to the goalPoint.
 */
void GoToPoint::behave() {
	vector<Behavior*> behaviors = getBehaviors();
	vector<Behavior*>::iterator behaviorsIterator = behaviors.begin();

	// TurnInPlace behavior
	Behavior * turnInPlacebehavior = *(behaviorsIterator).operator ->();
	_robot->Read();

	if (turnInPlacebehavior->startCondition()) {
		while (!turnInPlacebehavior->stopCondition()) {
			turnInPlacebehavior->action();
		}

		// Consider to implement a stop method
		_robot->setSpeed((float) 0, (float) 0);
	}

	behaviorsIterator++;

	// GoForward behavior
	Behavior * goForwardBehavior = *(behaviorsIterator).operator ->();

	_robot->Read();

	if (goForwardBehavior->startCondition()) {
		int iterationIndex = 1;

		while (!goForwardBehavior->stopCondition()) {
			goForwardBehavior->action();

			if (iterationIndex++ > 10) {
				// IterationIndex reinitialization
				iterationIndex = 1;

				float neededYawDelta = calculateNeededYaw() - _robot->getLocation().getYaw();
				cout << "neededYawDelta: " << Helper::floatToString(neededYawDelta) << " compromizedYaw: " << Helper::floatToString(Helper::COMPROMISED_YAW) << endl;

				if (((neededYawDelta >= 0) && (neededYawDelta > Helper::COMPROMISED_YAW)) ||
					((neededYawDelta < 0) && (neededYawDelta < (-1 * Helper::COMPROMISED_YAW))))
					break;
			}
		}

		// Consider to implement a stop method
		_robot->setSpeed(0, 0);
	}

//	// Checks if the robot got stuck by an obstacle, if not, checking if the robot arrived to the goal location
//	// REMOVE THIS HORANI CAST
//	if (goForwardBehavior->isStuck()) {
//		// Navigating to the closest route point
//		Structs::Point closestRoutePoint = getClosestRoutePoint(_robot->getPosition());
//		GoToPoint * goToPointBehavior;
//
//		_robot->Read();
//
//		// Trying to get to the route point
//		while (_robot->getPosition().distanceBetweenPoints(closestRoutePoint) > Helper::COMPROMISED_DISTANCE) {
//			goToPointBehavior = new GoToPoint(_robot, _localizationManager, closestRoutePoint);
//
//			_robot->Read();
//
//			if (goToPointBehavior->startCondition()) {
//				while (!goToPointBehavior->stopCondition()) {
//					goToPointBehavior->action();
//				}
//			}
//		}
//	} else if (!isGoalLocationReached()) {
	if (!isGoalLocationReached()) {
		initializeGoToPointBehavior();

		action();
	}
}
