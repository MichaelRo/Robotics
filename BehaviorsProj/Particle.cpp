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
Particle::Particle(float x, float y, float yaw, float belief, Map * map) : Particle(Structs::Location(x, y, yaw), belief, map) {

}

/**
	Initializes the Particle.

	@param location - the location of the particle.
	@param belief - the belief of the particle.
	@param map - the map that the particle.
*/
Particle::Particle(Structs::Location location, float belief, Map * map) {
	_id = ++PARTICLE_ID_SEQUENCE;
	_map = map;
	_belief = belief;
	Structs::Location deltaLocation = (_id == 1) ? (Structs::Location()) : getRandomDeltaLocation();
	Structs::Location newLocation = location + deltaLocation;
	_location = newLocation;
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
float Particle::getBelief() {
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
float Particle::update(Structs::Location destination, vector<float> laserScan) {
	_belief = calculateBelief(destination, laserScan);

	_location.setX(_location.getX() + destination.getX());
	_location.setY(_location.getY() + destination.getY());
	_location.setYaw(_location.getYaw() + destination.getYaw());

	return _belief;
}

/**
	CalculatePredictedBelief of this particle.

	@param destination - the destination location of the particle.
	@return - the belief of the particle.
 */
float Particle::calculatePredictedBelief(Structs::Location destination) {
	return calculateMotionModelProbability(destination) * getBelief();
}

/**
	CalculateBelief of this particle.

	@param destination - the destination location of the particle.
	@param laserScan - the result of the laser scan of the robot.
	@return - the belief of the particle.
 */
float Particle::calculateBelief(Structs::Location destination, vector<float> laserScan) {
	return NORMALIZATION_FACTOR * checkObservationModel(laserScan) * calculatePredictedBelief(destination);
}

/**
	CalculateMotionModelProbability of this particle.

	@param destination - the destination location of the particle.
	@return - the calculated propability of the particle.
 */
float Particle::calculateMotionModelProbability(Structs::Location destination) {
	float distance = _location.pointValue().distanceBetweenPoints(destination.pointValue());
	float yaw = abs(destination.getYaw());

	float propability = 0.25;

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
float Particle::checkObservationModel(vector<float> laserScan) {
	int expectedObsticlesDetected = 0;

	for (unsigned int laserDegree = 0; laserDegree < laserScan.size(); laserDegree += 10) {
		float currentLaserScan = laserScan[laserDegree];

		if (isObsticleDetectedAsExpected(currentLaserScan, laserDegree))
			expectedObsticlesDetected++;
	}

	return expectedObsticlesDetected / (laserScan.size() / 10);
}

/**
	createDescendantParticles of this particle.

	@param amount - the amount of the descendant particles to create.
	@return - the created descendant particles.
 */
list<Particle> Particle::createDescendantParticles(int amount) {
	// The LocaliztionManager should create descendants, it should give a random location / delta destination as well
	list<Particle> descendantParticles = list<Particle>();

	for (int index = 0; index < amount; index++) {
		descendantParticles.push_back(Particle(_location, _belief * 0.9, _map));
	}

	return descendantParticles;
}

/**
	Check if obsticle detected as expected.

	@param laserScan - the result of the laser scan of the robot.
	@param laserDegree - the yaw of the result.
	@return - if obsticle detected as expected.
 */
bool Particle::isObsticleDetectedAsExpected(float laserScan, int laserDegree) {
	int correctDetectionsNumber = 0;
	int incorrectDetectionsNumber = 0;

	// CONSIDER IMPLEMENTING A METHOD FOR FINDING THE SPOTTED POINT CELL VALUE

	// Going through all the spotted points in the lasers way (without the laser scanned point)
	// Maybe ceil ?
	for (int distanceFromSpottedPoint = 1; distanceFromSpottedPoint < floor(METER_TO_CM(laserScan)); distanceFromSpottedPoint += 10) {
		// Calculating the spotted point location (as a delta to the particle itself)

		// Laser degree as an offset, plus or minus depends on the laser scan start direction
		float spottedPointYaw = M_PI - Helper::degreesToRadians(getLocation().getYaw() + laserDegree);
		float deltaX = cos(spottedPointYaw) * distanceFromSpottedPoint;
		float deltaY = sin(spottedPointYaw) * distanceFromSpottedPoint;

		// Maybe ceil or floor?
		Structs::Point spottedPoint(round(_location.getX() + deltaX), round(_location.getY() + deltaY));

		if ((spottedPoint.getX() >= 0 && spottedPoint.getX() < _map->getWidth()) &&
			(spottedPoint.getY() >= 0 && spottedPoint.getY() < _map->getHeight())) {
			int spottedPointValue = _map->getCellValue(spottedPoint, _map->getMapResolution());

			if (spottedPointValue == Map::OCCUPIED_CELL) {
				// If the spotted point, which stands in the way to the laser current scan, is occupied - the laser was supposed to detect an obstacle
				incorrectDetectionsNumber++;
			} else {
				// The spotted point stands in the way to the laser current scan supposed to be free, otherwise the laser scan would be smaller
				correctDetectionsNumber++;
			}
		} else {
			break;
		}
	}

	// Checking the laser scanned point in case that the laser scan is smaller than the maximum range
	if (laserScan < Helper::LASER_MAX_DETECTION_RANGE) {
		// Calculating the laser scanned point (as a delta to the particle itself)
		// Laser degree as an offset, plus or minus depends on the laser scan start direction
		float spottedPointYaw = M_PI - Helper::degreesToRadians(getLocation().getYaw() + laserDegree);
		float deltaX = cos(spottedPointYaw) * floor(METER_TO_CM(laserScan));
		float deltaY = sin(spottedPointYaw) * floor(METER_TO_CM(laserScan));

		// Maybe ceil or floor?
		Structs::Point spottedPoint(round(_location.getX() + deltaX), round(_location.getY() + deltaY));

		if ((spottedPoint.getX() >= 0 && spottedPoint.getX() < _map->getWidth()) &&
			(spottedPoint.getY() >= 0 && spottedPoint.getY() < _map->getHeight())) {
			int spottedPointValue = _map->getCellValue(spottedPoint, _map->getMapResolution());

			if (spottedPointValue == Map::OCCUPIED_CELL) {
				// The spotted laser scan is occupied - the particle is probably in the right place
				correctDetectionsNumber++;
			} else {
				// If the spotted laser scan isn't occupied - the particle probably isn't in the right place
				incorrectDetectionsNumber++;
			}
		}
	}

	return correctDetectionsNumber > incorrectDetectionsNumber;
}

/**
	GetRandomDeltaLocation to a new particle.

	@return - the random location.
 */
Structs::Location Particle::getRandomDeltaLocation() {
	int xBoundary = floor((_map->getWidth() / 2) * MAX_PARTICLES_RELATIVE_RATIO_CREATION);
	int yBoundary = floor((_map->getHeight() / 2) * MAX_PARTICLES_RELATIVE_RATIO_CREATION);
	int yawBoundary = floor((360 / 2) * MAX_PARTICLES_RELATIVE_YAW_CREATION);

	// Generates random number between negative and positive boundaries (same value)
	int x = (rand() % (2 * xBoundary)) - xBoundary;
	int y = (rand() % (2 * yBoundary)) - yBoundary;
	int yaw = (rand() % (2 * yawBoundary)) - yawBoundary;

	Structs::Location randomLocation = Structs::Location(x, y, yaw);

	return randomLocation;
}
