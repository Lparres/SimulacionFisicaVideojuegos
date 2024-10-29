#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(std::list<Particle*>& globalList, Vector3D<> gravityaceleration) :
	ForceGenerator(globalList),
	gravityAceleration(gravityaceleration)
{
}

GravityForceGenerator::~GravityForceGenerator()
{
}

void GravityForceGenerator::ApplyForceToParticles(double t)
{
	for (Particle* p : globalListRef) {
		p->ApplyForce(gravityAceleration * t);
	}
}
