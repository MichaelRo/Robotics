/*
 * Particle.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Particle.h"

int Particle::PARTICLE_ID_SEQUENCE = 0;

/**
	Destructs Particle.
*/
Particle::~Particle() {

}

/**
	Initializes the Particle.

	@param x - the x index of the particle.
	@param y - the y index of the particle.
	@param yaw - the yaw of the particle.
	@param belief - the belief of the particle.
	@param map - the map that the particle.
*/
Particle::Particle(double x, double y, double yaw, double belief, Map * map) : Particle(Structs::Location(x, y, yaw), belief, map) {

}

/**
	Initializes the Particle.

	@param location - the location of the particle.
	@param belief - the belief of the particle.
	@param map - the map that the particle.
*/
Particle::Particle(Structs::Location location, double belief, Map * map) {
	_id = ++PARTICLE_ID_SEQUENCE;
	_map = map;
	_belief = belief;
	_location = location;
}

/**
	This method implement the operator == of the object Particle.
	in this case by equalization by the id of the particle.

	@return - is the ids of the two particles equals.
 */
bool Particle::operator ==(const Particle & particle) const {
	return _id == particle._id;
}

/**
	GetBelief of this particle.

	@return - the belief of the particle.
 */
double Particle::getBelief() {
	return _belief;
}

/**
	GetLocation of this particle.

	@return - the belief of the particle.
 */
Structs::Location Particle::getLocation() {
	return _location;
}

/**
	Update the details of the Particle.

	@param destination - the destination location of the particle.
	@param laserScan - the result of the laser scan of the robot.
	@return - the belief of the particle.
*/
double Particle::update(Structs::Location destinationDelta, vector<double> laserScan) {
	Structs::Location deltaLocation = destinationDelta + getRandomDeltaLocation();

	_belief = calculateBelief(deltaLocation, laserScan);

	_location.setX(_location.getX() + deltaLocation.getX());
	_location.setY(_location.getY() + deltaLocation.getY());
	_location.setYaw(_location.getYaw() + deltaLocation.getYaw());

	return _belief;
}

/**
	CalculatePredictedBelief of this particle.

	@param destination - the destination location of the particle.
	@return - the belief of the particle.
 */
double Particle::calculatePredictedBelief(Structs::Location destinationDelta) {
	return calculateMotionModelProbability(destinationDelta) * getBelief();
}

/**
	CalculateBelief of this particle.

	@param destination - the destination location of the particle.
	@param laserScan - the result of the laser scan of the robot.
	@return - the belief of the particle.
 */
double Particle::calculateBelief(Structs::Location destinationDelta, vector<double> laserScan) {
	double belief = NORMALIZATION_FACTOR * checkObservationModel(laserScan) * calculatePredictedBelief(destinationDelta);

	return (belief > 1) ? 1 : belief;
}

/**
	CalculateMotionModelProbability of this particle.
	NOTE: remove the comments mark before adding LocalizationManager

	@param destination - the destination location of the particle.
	@return - the calculated propability of the particle.
 */
double Particle::calculateMotionModelProbability(Structs::Location destinationDelta) {
	double distance = _location.pointValue().distanceBetweenPoints(destinationDelta.pointValue());
	double yaw = abs(destinationDelta.getYaw());

	double propability = 0.25;

	if (distance <= MAX_DISTANCE)
		propability += 0.25;
	if (yaw <= MAX_YAW)
		propability += 0.25;
	if (yaw == 0)
		propability += 0.25;

	return propability;
}

/**
	CheckObservationModel of this particle.

	@param laserScan - the result of the laser scan of the robot.
	@return - the check if there is an obsticle by the result of the laser scan of the robot.
 */
double Particle::checkObservationModel(vector<double> laserScan) {
	int expectedObsticlesDetected = 0;

	for (unsigned int laserDegree = 0; laserDegree < laserScan.size(); laserDegree += 4) {
		double currentLaserScan = laserScan[laserDegree];

		if (isObsticleDetectedAsExpected(currentLaserScan, laserDegree))
			expectedObsticlesDetected++;
	}

	return expectedObsticlesDetected / (laserScan.size() / 4);
}

/**
	createDescendantParticles of this particle.

	@param amount - the amount of the descendant particles to create.
	@return - the created descendant particles.
 */
void Particle::createDescendantParticles(int amount, list<Particle> * list) {
	// The LocaliztionManager should create descendants, it should give a random location / delta destination as well
	for (int index = 0; index < amount; index++) {
		list->push_back(Particle(_location, _belief * 0.9, _map));
	}
}

/**
	Check if obsticle detected as expected.
	NOTE: remove the comments mark before adding LocalizationManager

	@param laserScan - the result of the laser scan of the robot.
	@param laserDegree - the yaw of the result.
	@return - if obsticle detected as expected.
 */
bool Particle::isObsticleDetectedAsExpected(double laserScan, int laserDegree) {
	int correctDetectionsNumber = 0;
	int incorrectDetectionsNumber = 0;

	// Going through all the spotted points in the lasers way (without the laser scanned point)
	for (int distanceFromSpottedPoint = 1; distanceFromSpottedPoint < floor(METER_TO_CM(laserScan)); distanceFromSpottedPoint += 10) {
		// Calculating the spotted point location (as a delta to the particle itself)

		// Laser degree as an offset, plus or minus depends on the laser scan start direction
		double spottedPointYaw = M_PI - Helper::degreesToRadians(getLocation().getYaw() + laserDegree);
		double deltaX = cos(spottedPointYaw) * distanceFromSpottedPoint;
		double deltaY = sin(spottedPointYaw) * distanceFromSpottedPoint;

		Structs::Point spottedPoint(round(_location.getX() + deltaX), round(_location.getY() + deltaY));

		if ((spottedPoint.getX() >= 0) && (spottedPoint.getX() < _map->getWidth()) &&
			(spottedPoint.getY() >= 0) && (spottedPoint.getY() < _map->getHeight())) {
			int spottedPointValue = _map->getCellValue(spottedPoint, _map->getMapResolution());

			if (spottedPointValue == Globals::CellType::OCCUPIED_CELL) {
				// If the spotted point, which stands in the way to the laser current scan, is occupied - the laser was supposed to detect an obstacle
				incorrectDetectionsNumber++;
			} else {
				// The spotted point stands in the way to the laser clurrent scan supposed to be free, otherwise the laser scan would be smaller
				correctDetectionsNumber++;
			}
		} else {
			break;
		}
	}

	// Checking the laser scanned point in case that the laser scan is smaller than the maximum range
	if (laserScan < Globals::LASER_MAX_DETECTION_RANGE) {
		// Calculating the laser scanned point (as a delta to the particle itself)
		// Laser degree as an offset, plus or minus depends on the laser scan start direction
		double spottedPointYaw = M_PI - Helper::degreesToRadians(getLocation().getYaw() + laserDegree);
		double deltaX = cos(spottedPointYaw) * floor(METER_TO_CM(laserScan));
		double deltaY = sin(spottedPointYaw) * floor(METER_TO_CM(laserScan));

		Structs::Point spottedPoint(round(_location.getX() + deltaX), round(_location.getY() + deltaY));

		if ((spottedPoint.getX() >= 0 && spottedPoint.getX() < _map->getWidth()) &&
			(spottedPoint.getY() >= 0 && spottedPoint.getY() < _map->getHeight())) {
			int spottedPointValue = _map->getCellValue(spottedPoint, _map->getMapResolution());

			if (spottedPointValue == Globals::CellType::OCCUPIED_CELL) {
				// The spotted laser scan is occupied - the particle is probably in the right place
				correctDetectionsNumber++;
			} else {
				// If the spotted laser scan isn't occupied - the particle probably isn't in the right place
				incorrectDetectionsNumber++;
			}
		}
	}

	return correctDetectionsNumber > (correctDetectionsNumber + incorrectDetectionsNumber);
}

/**
	GetRandomDeltaLocation to a new particle.

	@return - the random location.
 */
Structs::Location Particle::getRandomDeltaLocation() {
	int xBoundary = floor((_map->getWidth() / 2) * Globals::MAX_PARTICLES_RELATIVE_RATIO_CREATION);
	int yBoundary = floor((_map->getHeight() / 2) * Globals::MAX_PARTICLES_RELATIVE_RATIO_CREATION);
	int yawBoundary = floor((360 / 2) * Globals::MAX_PARTICLES_RELATIVE_YAW_CREATION);

	// Generates random number between negative and positive boundaries (same value)
	int x = (rand() % (2 * xBoundary)) - xBoundary;
	int y = (rand() % (2 * yBoundary)) - yBoundary;
	int yaw = (rand() % (2 * yawBoundary)) - yawBoundary;

	Structs::Location randomLocation = Structs::Location(x, y, yaw);

	return randomLocation;
}
