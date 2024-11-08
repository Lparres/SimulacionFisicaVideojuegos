#pragma once
#include "ForceGenerator.h"
#include "RenderUtils.hpp"

class ExplosionForceGenerator : public ForceGenerator
{
public:
	ExplosionForceGenerator(float explosionForce, float explosionRadius, Vector3D<> position);
	~ExplosionForceGenerator();

	void UpdateForce(Particle* p, double t) override;

	void keyPress(unsigned char key, const physx::PxTransform& camera);

private:
	float explosionForce;
	float explosionRadius;
	Vector3D<> position;
	bool explosionActive;
};

