#pragma once

#include "Vector3D.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include <random>

class ParticleGenerator
{
public:
	ParticleGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef);
	~ParticleGenerator();

	void SetID(int id) { this->id = id; };
	int GetID() { return id; };

	virtual void GenerateParticle() = 0;

	void SetParticleModel(Particle* p) { particleModel = p; };

protected:
	int id;
	Vector3D<> position;
	Vector3D<> direction;
	float speed;
	float angleDelta;
	float speedDelta;

	Particle* particleModel; 
	
	ParticleSystem* systemRef;

	std::mt19937 randomGen;
};

