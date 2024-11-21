#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other) :
	_k(k),
	_resting_length(resting_length),
	_other(other)
{
}

SpringForceGenerator::~SpringForceGenerator()
{
}

void SpringForceGenerator::UpdateForce(Particle* particle, double t)
{
	// "particle" is the particle to apply the force
	Vector3D<> relative_pos_vector = _other->GetPosition() - particle->GetPosition();
	
	float length = relative_pos_vector.GetMagnitude();
	float deltaX = length - _resting_length;

	Vector3D<> force = relative_pos_vector.GetNormalized() * deltaX * _k;

	particle->ApplyInstantForce(force * t);
}


