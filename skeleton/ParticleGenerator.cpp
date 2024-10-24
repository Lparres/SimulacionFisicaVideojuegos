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
	particleModel = new Particle(position, direction * speed, physx::PxGeometryType::Enum::eSPHERE, 1, physx::PxVec4(1.0, 1.0, 0.0, 1.0));

	std::random_device rd;
	randomGen = std::mt19937(rd());
}

ParticleGenerator::~ParticleGenerator()
{
}
