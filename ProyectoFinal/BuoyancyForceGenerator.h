#pragma once
#include "ForceGenerator.h"
class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float V, float d, Particle* liquid_particle);
	virtual ~BuoyancyForceGenerator();

	virtual void UpdateForce(Particle* p, double t) override;

protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity;

	Particle* _liquid_particle;
};

