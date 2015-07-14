/*
 * Particle.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Particle.h"

int Particle::PARTICLE_ID_SEQUENCE = 0;

Particle::~Particle() {

}

Particle::Particle(float x, float y, float yaw, float belief, MapForRobot * map) {
	_map = map;
	_belief = belief;
	Structs::Location deltaLocation = getRandomDeltaLocation();
	Structs::Location newLocation(x + deltaLocation.getX(),
								  y + deltaLocation.getY(),
								  yaw + deltaLocation.getYaw());
	_location = newLocation;
	_id = PARTICLE_ID_SEQUENCE++;

	cout << "Particle was created at: " << _location.toString() << "." << endl;
}

Particle::Particle(Structs::Location location, float belief, MapForRobot * map) {
	_map = map;
	_belief = belief;
	Structs::Location deltaLocation = getRandomDeltaLocation();
	Structs::Location newLocation = location + deltaLocation;
	_location = newLocation;
	_id = PARTICLE_ID_SEQUENCE++;
}

bool Particle::operator ==(const Particle & particle) const {
	return _id == particle._id;
}

float Particle::getBelief() {
	return _belief;
}

Structs::Location Particle::getLocation() {
	return _location;
}

float Particle::update(Structs::Location destination, vector<float> laserScan) {
	_location.setX(_location.getX() + destination.getX());
	_location.setY(_location.getY() + destination.getY());
	_location.setYaw(_location.getYaw() + destination.getYaw());
	_belief = calculateBelief(destination, laserScan);

	return _belief;
}

float Particle::calculatePredictedBelief(Structs::Location destination) {
	return calculateMotionModelProbability(destination) * getBelief();
}

float Particle::calculateBelief(Structs::Location destination, vector<float> laserScan) {
	return NORMALIZATION_FACTOR * checkObservationModel(laserScan) * calculatePredictedBelief(destination);
}

float Particle::calculateMotionModelProbability(Structs::Location destination) {
	float distance = getDistance(destination);
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

float Particle::checkObservationModel(vector<float> laserScan) {
	int expectedObsticlesDetected;

	for (unsigned int laserDegree = 0; laserDegree < laserScan.size(); laserDegree++) {
		float currentLaserScan = laserScan[laserDegree];

		expectedObsticlesDetected = 0;

		if (isObsticleDetectedAsExpected(currentLaserScan, laserDegree))
			expectedObsticlesDetected++;
	}

	return expectedObsticlesDetected / laserScan.size();
}

list<Particle> Particle::createDescendantParticles(int amount) {
	// The LocaliztionManager should create descendants, it should give a random location / delta destination as well
	list<Particle> descendantParticles = list<Particle>();

	for (int index = 0; index < amount; index++) {
//		descendantParticles.push_back(Particle(_location, _belief, _map));
		descendantParticles.push_back(Particle(_location, _belief * 0.9, _map));
	}

	return descendantParticles;
}

float Particle::getDistance(Structs::Location destination) {
	return sqrt((destination.getX() * destination.getX()) + (destination.getY() * destination.getY()));
}

bool Particle::isObsticleDetectedAsExpected(float laserScan, int laserDegree) {
	int correctDetectionsNumber = 0;
	int falseDetectionsNumber = 0;

	if (laserScan < LASER_MAX_RANGE) {
//		for (int j = Helper::SENSOR_FROM_END; j <= Helper::SENSOR_DETECTION_RANGE; j +=  Helper::CELL_DIMENSION) {
		for (int j = Helper::SENSOR_FROM_END; j <= Helper::SENSOR_DETECTION_RANGE; j++) {
			Structs::Location detectedLocationInMap(_location.getX() + (cos(detectedLocationInMap.getYaw()) * j),
													_location.getY() + (sin(detectedLocationInMap.getYaw()) * j),
													_location.getYaw() + DEGREES_TO_RADIANS(laserDegree));

			int detectedLocationValue = _map->getCellValue(detectedLocationInMap.getX(), detectedLocationInMap.getY());

			if (detectedLocationValue == Map::FREE_CELL) {
				correctDetectionsNumber++;
			} else if (detectedLocationValue == Map::OCCUPIED_CELL) {
				falseDetectionsNumber++;
			}
		}
	} else {
		Structs::Location detectedLocationInMap(_location.getX() + (cos(detectedLocationInMap.getYaw()) * METER_TO_CM(laserScan)),
												_location.getY() + (sin(detectedLocationInMap.getYaw()) * METER_TO_CM(laserScan)),
												_location.getYaw() + DEGREES_TO_RADIANS(laserDegree));

		int detectedLocationValue = _map->getCellValue(detectedLocationInMap.getX(), detectedLocationInMap.getY());

		if (detectedLocationValue == Map::FREE_CELL) {
			falseDetectionsNumber++;
		} else if (detectedLocationValue == Map::OCCUPIED_CELL) {
			correctDetectionsNumber++;
		}
	}

//	return correctDetectionsNumber / (correctDetectionsNumber + falseDetectionsNumber);

	// ????
	return correctDetectionsNumber > falseDetectionsNumber;
}

Structs::Location Particle::getRandomDeltaLocation() {

	int xBoundary = floor(_map->getWidth() * MAX_PARTICLES_RELATIVE_RATIO_CREATION);
	int yBoundary = floor(_map->getHeight() * MAX_PARTICLES_RELATIVE_RATIO_CREATION);

	// Generates random number between negative and positive boundaries (same value)
	int x = (rand() % (2 * xBoundary)) - xBoundary;
	int y = (rand() % (2 * yBoundary)) - yBoundary;
	// Change the 0.5 to a real boundary defining number
	double yaw = ((double) rand() / (RAND_MAX)) - 0.5;

	Structs::Location randomLocation = Structs::Location(x, y, yaw);

	return randomLocation;
}
