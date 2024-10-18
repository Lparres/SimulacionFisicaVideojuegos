#include "ParticleGaussianGenerator.h"

ParticleGaussianGenerator::ParticleGaussianGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef) :
	ParticleGenerator(position, direction, speed, angleDelta, speedDelta, systemRef)
{}


ParticleGaussianGenerator::~ParticleGaussianGenerator()
{

}

void ParticleGaussianGenerator::GenerateParticle()
{

}
