#pragma once
#include "ForceGenerator.h"
#include "RenderUtils.hpp"

class ExplosionForceGenerator : public ForceGenerator
{
public:
	ExplosionForceGenerator(float explosionForce, float explosionRadius, Vector3D<> position);
	~ExplosionForceGenerator();

	void UpdateForce(Particle* p, double t) override;

private:
	float explosionForce;
	float explosionRadius;
	Vector3D<> position;
};

