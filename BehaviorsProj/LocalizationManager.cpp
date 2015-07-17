/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "LocalizationManager.h"

LocalizationManager::~LocalizationManager() {

}

LocalizationManager::LocalizationManager(Structs::Location startLocation, Map * map) {
	_map = map;
	srand(time(NULL));

	// Initializing the particles list by the PARTICLES_AMOUNT value
	_particles.push_back(Particle(startLocation, (float) 1, map));

	list<Particle> descendantParticles = getHighestBeliefParticle()->createDescendantParticles(Helper::TOTAL_PARTICLES_AMOUNT - 1);
	_particles.insert(_particles.end(), descendantParticles.begin(), descendantParticles.end());
}

void LocalizationManager::updateParticles(Structs::Location destination, vector<float> laserScan) {
	list<Particle> particlesForDelete = list<Particle>();
	list<Particle> particlesForMultiply = list<Particle>();

	for (list<Particle>::iterator particlesIterator = _particles.begin(); particlesIterator != _particles.end(); particlesIterator++) {
		float currentParticleBelief = particlesIterator->update(destination, laserScan);

		if (currentParticleBelief < BELIEF_THRESHOLD) {
			if (particlesForDelete.size() < 4) {
				particlesForDelete.push_back(*particlesIterator.operator ->());
			} else {
				for (list<Particle>::iterator particlesForDeleteIterator = particlesForDelete.begin(); particlesForDeleteIterator != particlesForDelete.end(); particlesForDeleteIterator++) {
					if (particlesForDeleteIterator->getBelief() > particlesIterator->getBelief()) {
						particlesForDelete.erase(particlesForDeleteIterator++);
						particlesForDelete.push_back(*particlesIterator.operator ->());

						break;
					}
				}
			}
		} else {
			if (particlesForMultiply.size() < 2) {
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

float LocalizationManager::getHighestBelief() {
	return getHighestBeliefParticle()->getBelief();
}

Structs::Location LocalizationManager::getProbableLocation() {
	return getHighestBeliefParticle()->getLocation();
}
