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

Particle::Particle(float x, float y, float yaw, Map * map) {
	_map = map;
	_belief = 1;
	Structs::Location deltaLocation = getRandomDeltaLocation();
	Structs::Location newLocation(x + deltaLocation._x,
								  y + deltaLocation._y,
								  yaw + deltaLocation._yaw);
	_location = newLocation;
	_id = PARTICLE_ID_SEQUENCE++;

	cout << "Particle was created at: " << _location.toString() << "." << endl;
}

Particle::Particle(Structs::Location location, Map * map) {
	_map = map;
	_belief = 1;
	Structs::Location deltaLocation = getRandomDeltaLocation();
	Structs::Location newLocation = location + deltaLocation;
	_location = newLocation;
	_id = PARTICLE_ID_SEQUENCE++;

	cout << "Particle was created at: " << _location.toString() << "." << endl;
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
	cout << "Particle " << _location.toString();

	_location._x += destination._x;
	_location._y += destination._y;
	_location._yaw += destination._yaw;
	_belief = calculateBelief(destination, laserScan);

	cout << "was updated to: " << _location.toString() << ", with belief: " << _belief << "." << endl;

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
	float yaw = abs(destination._yaw);

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

	for (int laserDegree = 0; laserDegree < Helper::DEGREES; laserDegree++) {
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
		descendantParticles.push_back(Particle(_location, _map));
	}

	return descendantParticles;
}

float Particle::getDistance(Structs::Location destination) {
	return sqrt((destination._x * destination._x) + (destination._y * destination._y));
}

bool Particle::isObsticleDetectedAsExpected(float laserScan, int laserDegree) {
	int correctDetectionsNumber = 0;
	int falseDetectionsNumber = 0;

	if (laserScan < LASER_MAX_RANGE) {
		for (int j = Helper::SENSOR_FROM_END; j <= Helper::SENSOR_DETECTION_RANGE; j +=  Helper::CELL_DIMENSION) {
			Structs::Location detectedLocationInMap(_location._x + (cos(detectedLocationInMap._yaw) * j),
													_location._y + (sin(detectedLocationInMap._yaw) * j),
													_location._yaw + DEGREES_TO_RADIANS(laserDegree));

			int detectedLocationValue = _map->getCellValue(detectedLocationInMap._x, detectedLocationInMap._y, _map->getMapResolution());

			if (detectedLocationValue == Map::FREE_CELL) {
				correctDetectionsNumber++;
			} else if (detectedLocationValue == Map::OCCUPIED_CELL) {
				falseDetectionsNumber++;
			}
		}
	} else {
		Structs::Location detectedLocationInMap(_location._yaw + DEGREES_TO_RADIANS(laserDegree),
												_location._x + (cos(detectedLocationInMap._yaw) * METER_TO_CM(laserScan)),
												_location._y + (sin(detectedLocationInMap._yaw) * METER_TO_CM(laserScan)));

		int detectedLocationValue = _map->getCellValue(detectedLocationInMap._x, detectedLocationInMap._y, _map->getMapResolution());

		if (detectedLocationValue == Map::FREE_CELL) {
			falseDetectionsNumber++;
		} else if (detectedLocationValue == Map::OCCUPIED_CELL) {
			correctDetectionsNumber++;
		}
	}

	return correctDetectionsNumber / (correctDetectionsNumber + falseDetectionsNumber);
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
