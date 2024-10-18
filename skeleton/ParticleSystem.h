#pragma once

#include <list>
#include "Vector3D.h"

class ParticleGenerator;
class Particle;

#define MAX_DISTANCE 100

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	int AddNormalGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta);
	int AddGaussianGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta);

	void AddParticle(Vector3D<> position, Vector3D<> velocity);

	void Update(double t);

private:
	std::list<ParticleGenerator*> generators;
	std::list<Particle*> particles;

	void GenerateParticles();
	void KillParticles();
	void UpdateParticles(double t);
};

