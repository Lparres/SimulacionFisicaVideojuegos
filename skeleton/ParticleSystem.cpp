#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::AddGenerator(ParticleGenerator generator)
{
	generator.SetID(generators.size());
	generators.push_back(new ParticleGenerator(generator));
}

ParticleGenerator* ParticleSystem::AddGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta)
{
	ParticleGenerator* generator = new ParticleGenerator(position, direction, speed, angleDelta, speedDelta);
	generator->SetID(generators.size());
	generators.push_back(generator);
	return generator;
}
