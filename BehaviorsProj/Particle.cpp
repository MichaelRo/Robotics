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
	_location = Structs::Location(x, y, yaw);
	_map = map;
	_belief = 1;
}

Particle::Particle(Structs::Location location, Map* map) {
	_location = location;
	_map = map;
	_belief = 1;
}

float Particle::getBelief() {
	return _belief;
}

Structs::Location Particle::getLocation() {
	return _location;
}

float Particle::update(Structs::Location destination, vector<float> laserScan) {
	_location.x += destination.x;
	_location.y += destination.y;
	_location.yaw += destination.yaw;

	return _belief = calculateBelief(destination);
}

float Particle::calculatePredictedBelief(Structs::Location destination) {
	return calculateMotionModelProbability(destination) * getBelief();
}

float Particle::calculateBelief(Structs::Location destination) {
	return NORMALIZATION_FACTOR * getObservationModel(destination) * calculatePredictedBelief(destination);
}

float Particle::calculateMotionModelProbability(Structs::Location destination) {
	float distance = getDistance(destination);
	float yaw = abs(destination.yaw);

	float propability = 0.25;

	if (distance <= MAX_DISTANCE)
		propability += 0.25;
	if (yaw <= MAX_YAW)
		propability += 0.25;
	if (yaw == 0)
		propability += 0.25;

	return propability;
}

float Particle::getObservationModel(Structs::Location destination) {
	// Probably getting it from the robot / localiztionManager
}

vector<Particle> Particle::createDescendantParticles(int amount) {
	// The LocaliztionManager should create descendants, it should give a random location / delta destination as well

	vector<Particle> descendantParticles = vector<Particle>();

	for (int index = 0; index < amount; index++) {
		descendantParticles.push_back(Particle(_location, _map));
	}

	return descendantParticles;
}

float Particle::getDistance(Structs::Location destination) {
	return sqrt((destination.x * destination.x) + (destination.y * destination.y));
}
