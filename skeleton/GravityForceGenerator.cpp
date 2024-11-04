#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(Vector3D<> gravityaceleration) :
	ForceGenerator(),
	gravityAceleration(gravityaceleration)
{
}

GravityForceGenerator::~GravityForceGenerator()
{
}

void GravityForceGenerator::UpdateForce(Particle* p, double t)
{
	p->AddInstantForce(gravityAceleration * t);
}
