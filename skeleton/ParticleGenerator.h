#pragma once

#include "Vector3D.h"
#include "Particle.h"

class ParticleGenerator
{
public:
	ParticleGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta);
	~ParticleGenerator();

	void SetID(int id) { this->id = id; };

private:
	int id;
	Vector3D<> position;
	Vector3D<> direction;
	float speed;
	float angleDelta;
	float speedDelta;

	Particle* particleModel;
};

