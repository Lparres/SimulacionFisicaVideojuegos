#pragma once

#include <list>
#include "ParticleGenerator.h"
#include "Vector3D.h"

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void AddGenerator(ParticleGenerator generator);
	ParticleGenerator* AddGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta);

private:
	std::list<ParticleGenerator*> generators;
};

