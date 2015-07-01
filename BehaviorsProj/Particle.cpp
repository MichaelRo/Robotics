/*
 * Particle.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Particle.h"

Particle::~Particle() {
	delete _map;
}

Particle::Particle(float x, float y, float yaw, Map* map) {
	Structs::Location * deltaLocation = getRandomDeltaLocation();
	Structs::Location newLocation(x + deltaLocation->x,
								  y + deltaLocation->y,
								  yaw + deltaLocation->yaw);
	_location = &newLocation;
	_map = map;
	_belief = 1;
}

Particle::Particle(Structs::Location * location, Map* map) {
	Structs::Location * deltaLocation = getRandomDeltaLocation();
	Structs::Location newLocation(location->x + deltaLocation->x,
								  location->y + deltaLocation->y,
								  location->yaw + deltaLocation->yaw);
	_location = &newLocation;
	_map = map;
	_belief = 1;
}

float Particle::getBelief() {
	return _belief;
}

Structs::Location * Particle::getLocation() {
	return _location;
}

float Particle::update(Structs::Location * destination, vector<float> laserScan) {
	_location->x += destination->x;
	_location->y += destination->y;
	_location->yaw += destination->yaw;

	return _belief = calculateBelief(destination, laserScan);
}

float Particle::calculatePredictedBelief(Structs::Location * destination) {
	return calculateMotionModelProbability(destination) * getBelief();
}

float Particle::calculateBelief(Structs::Location * destination, vector<float> laserScan) {
	return NORMALIZATION_FACTOR * checkObservationModel(laserScan) * calculatePredictedBelief(destination);
}

float Particle::calculateMotionModelProbability(Structs::Location * destination) {
	float distance = getDistance(destination);
	float yaw = abs(destination->yaw);

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

	for (int laserIndex = 0; laserIndex < Helper::TOTAL_SCAN_SPAN; laserIndex++) {
		float currentLaserScan = laserScan[laserIndex];

		expectedObsticlesDetected = 0;

		if (isObsticleDetectedAsExpected(currentLaserScan, laserIndex))
			expectedObsticlesDetected++;
	}

	return expectedObsticlesDetected / laserScan.size();
}

vector<Particle> Particle::createDescendantParticles(int amount) {
	// The LocaliztionManager should create descendants, it should give a random location / delta destination as well

	vector<Particle> descendantParticles = vector<Particle>();

	for (int index = 0; index < amount; index++) {
		descendantParticles.push_back(Particle(_location, _map));
	}

	return descendantParticles;
}

float Particle::getDistance(Structs::Location * destination) {
	return sqrt((destination->x * destination->x) + (destination->y * destination->y));
}

bool Particle::isObsticleDetectedAsExpected(float laserScan, int laserIndex) {
	int correctDetectionsNumber = 0;
	int falseDetectionsNumber = 0;

	if (laserScan < LASER_MAX_RANGE) {
		for (int j = Helper::SENSOR_FROM_END; j <= Helper::SENSOR_DETECTION_RANGE; j +=  Helper::CELL_DIMENSION) {
			Structs::Location detectedLocationInMap(_location->yaw + DEGREES_TO_RADIANS(Helper::IndexToDegrees(laserIndex)),
													_location->x + (cos(detectedLocationInMap.yaw) * j),
													_location->y + (sin(detectedLocationInMap.yaw) * j));

			int detectedLocationValue = _map->getCellValue(detectedLocationInMap.x, detectedLocationInMap.y);

			if (detectedLocationValue == Map::FREE_CELL) {
				correctDetectionsNumber++;
			} else if (detectedLocationValue == Map::OCCUPIED_CELL) {
				falseDetectionsNumber++;
			}
		}
	} else {
		Structs::Location detectedLocationInMap(_location->yaw + DEGREES_TO_RADIANS(Helper::IndexToDegrees(laserIndex)),
												_location->x + (cos(detectedLocationInMap.yaw) * METER_TO_CM(laserScan)),
												_location->y + (sin(detectedLocationInMap.yaw) * METER_TO_CM(laserScan)));

		int detectedLocationValue = _map->getCellValue(detectedLocationInMap.x, detectedLocationInMap.y);

		if (detectedLocationValue == Map::FREE_CELL) {
			falseDetectionsNumber++;
		} else if (detectedLocationValue == Map::OCCUPIED_CELL) {
			correctDetectionsNumber++;
		}
	}

	return correctDetectionsNumber / (correctDetectionsNumber + falseDetectionsNumber);
}

Structs::Location * Particle::getRandomDeltaLocation() {
	int x = (rand() % (int) floor(_map->getWidth() * MAX_PARTICLES_RELATIVE_RATIO_CREATION));
	int y = (rand() % (int) floor(_map->getHeight() * MAX_PARTICLES_RELATIVE_RATIO_CREATION));
	int yaw = (rand() % (int) floor(DEGREES_TO_RADIANS(360) * MAX_PARTICLES_RELATIVE_YAW_CREATION));

	Structs::Location randomLocation = Structs::Location(x, y, yaw);

	return &randomLocation;
}
