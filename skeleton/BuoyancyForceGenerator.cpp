#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float V, float d, Particle* liquid_particle) :
	_height(h),
	_volume(V),
	_liquid_density(d),
	_gravity(9.8),
	_liquid_particle(liquid_particle)
{
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
}

void BuoyancyForceGenerator::UpdateForce(Particle* p, double t)
{
	float h = p->GetPosition().y;
	float h0 = _liquid_particle->GetPosition().y;

	Vector3D<> f(0, 0, 0);
	float immersed = 0.0;

	if (h - h0 > _height * 0.5) {
		immersed = 0.0;
	}
	else if (h - h0 < _height * 0.5) {
		// Totally immersed
		immersed = 1.0;
	} 
	else {
		immersed = (h0 - h) / _height + 0.5;
	}
	f.y = _liquid_density * _volume * immersed * 9.8;

	p->ApplyInstantForce(f * t);
}
