#pragma once

#include "Vector3D.h"
#include "Particle.h"
#include "ParticleSystem.h"

class ParticleGenerator
{
public:
	ParticleGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef);
	~ParticleGenerator();

	void SetID(int id) { this->id = id; };
	int GetID() { return id; };

	virtual void GenerateParticle() = 0;

protected:
	int id;
	Vector3D<> position;
	Vector3D<> direction;
	float speed;
	float angleDelta;
	float speedDelta;

	Particle* particleModel; 
	
	ParticleSystem* systemRef;
};

