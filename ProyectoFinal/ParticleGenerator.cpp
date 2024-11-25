#include "ParticleGenerator.h"
#include <random>

ParticleGenerator::ParticleGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef) :
	id(-1),
	position(position),
	direction(direction),
	speed(speed),
	angleDelta(angleDelta),
	speedDelta(speedDelta),
	systemRef(systemRef)
{
	std::random_device rd;
	randomGen = std::mt19937(rd());
}

ParticleGenerator::~ParticleGenerator()
{
}
