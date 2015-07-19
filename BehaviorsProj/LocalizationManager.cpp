/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "LocalizationManager.h"

/**
	Destructs LocalizationManager.
*/
LocalizationManager::~LocalizationManager() {

}

/**
	Initializes a LocalizationManager.

	@param startLocation - this value is start location of one particle.
	@param map - every particle save this map.
*/
LocalizationManager::LocalizationManager(Structs::Location startLocation, Map * map) {
	_map = map;
	_estimatedRobotLocation = startLocation;
	srand(time(NULL));

	// Initializing the particles list by the PARTICLES_AMOUNT value
	_particles.push_back(Particle(startLocation, (float) 1, map));

	list<Particle> descendantParticles = getHighestBeliefParticle()->createDescendantParticles(Helper::TOTAL_PARTICLES_AMOUNT);
	_particles.insert(_particles.end(), descendantParticles.begin(), descendantParticles.end());

	_particles.erase(_particles.begin());
}

void LocalizationManager::updateParticles(Structs::Location destinationDelta, Structs::Location estimatedRobotLocation, vector<float> laserScan) {
	_estimatedRobotLocation = _estimatedRobotLocation + destinationDelta;

	list<Particle> particlesForDelete = list<Particle>();
	list<Particle> particlesForMultiply = list<Particle>();

	for (list<Particle>::iterator particlesIterator = _particles.begin(); particlesIterator != _particles.end(); particlesIterator++) {
		float currentParticleBelief = particlesIterator->update(destinationDelta, laserScan);

//		cout << "Particle " << particlesIterator.operator ->()->getLocation().toString() << " belief is: " << currentParticleBelief << endl;

		if (currentParticleBelief < MINIMUM_BELIEF) {
			particlesForDelete.push_back(*particlesIterator.operator ->());
		} else {
			if (currentParticleBelief > BELIEF_THRESHOLD) {
				if (particlesForMultiply.size() < 4) {
					particlesForMultiply.push_back(*particlesIterator.operator ->());
				} else {
					for (list<Particle>::iterator particlesForMultiplyIterator = particlesForMultiply.begin(); particlesForMultiplyIterator != particlesForMultiply.end(); particlesForMultiplyIterator++) {
						if (particlesForMultiplyIterator->getBelief() < particlesIterator->getBelief()) {
							particlesForMultiply.erase(particlesForMultiplyIterator++);
							particlesForMultiply.push_back(*particlesIterator.operator ->());

							break;
						}
					}
				}
			}
		}
	}

	while (particlesForMultiply.size() < 3) {
		particlesForMultiply.push_back(Particle(_estimatedRobotLocation, 1, _map));
	}

	for (list<Particle>::iterator particlesForDeleteIterator = particlesForDelete.begin(); particlesForDeleteIterator != particlesForDelete.end(); particlesForDeleteIterator++) {
		Particle * particleForRemove = particlesForDeleteIterator.operator ->();

		_particles.remove(*particleForRemove);
	}

	if (particlesForMultiply.size() == 0)
		particlesForMultiply.push_back(*getHighestBeliefParticle());

	for (list<Particle>::iterator particlesForMultiplyIterator = particlesForMultiply.begin(); particlesForMultiplyIterator != particlesForMultiply.end(); particlesForMultiplyIterator++) {
		list<Particle> decendantParticles = particlesForMultiplyIterator->createDescendantParticles((Helper::TOTAL_PARTICLES_AMOUNT - _particles.size()) / particlesForMultiply.size());
		_particles.insert(_particles.end(), decendantParticles.begin(), decendantParticles.end());
	}
}

/**
	This method returns the best particle (with the highest belief).

	@return - the particle with the highest belief.
*/
// Maybe it should return a list so we can use it in updateParticles?
Particle * LocalizationManager::getHighestBeliefParticle() {
	list<Particle>::iterator particlesIterator = _particles.begin();
	Particle * highestBeliefParticle = particlesIterator.operator ->();

	for (particlesIterator = _particles.begin(); particlesIterator != _particles.end(); ++particlesIterator) {
		if (particlesIterator->getBelief() > highestBeliefParticle->getBelief())
			highestBeliefParticle = particlesIterator.operator ->();
	}

	return highestBeliefParticle;
}

/**
	This method returns the belief of the best particle (with the highest belief).

	@return - the belief of the particle with the highest belief.
*/
float LocalizationManager::getHighestBelief() {
	return getHighestBeliefParticle()->getBelief();
}

/**
	This method returns the location of best particle (with the highest belief).

	@return - the location of the particle with the highest belief.
*/
Structs::Location LocalizationManager::getProbableLocation() {
	return getHighestBeliefParticle()->getLocation();
}

/**
	Get map data member.

	@return - map.
*/
Map * LocalizationManager::getMap() {
	return _map;
}
