#pragma once

#include <list>
#include "Vector3D.h"

class ParticleGenerator;
class Particle;

#define MAX_DISTANCE 200
#define MAX_LIFETIME 10

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	int AddUniformGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta);
	int AddGaussianGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta);
	int AddRainGenerator(Vector3D<> position, float radius, int intensity);

	void AddParticle(Vector3D<> position, Vector3D<> velocity);

	void Update(double t);

private:
	std::list<ParticleGenerator*> generators;
	std::list<Particle*> particles;

	void GenerateParticles();
	void KillParticles();
	void UpdateParticles(double t);
};

