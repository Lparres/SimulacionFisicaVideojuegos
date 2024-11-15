#pragma once
#include "ForceGenerator.h"
#include "RenderUtils.hpp"

class ExplosionForceGenerator : public ForceGenerator
{
private:
	struct ShockWave {
		float radius;
		float speed;
		float time;
		
		ShockWave(float r, float s, float t) :
			radius(r), speed(s), time(t) {}
	};

public:
	ExplosionForceGenerator(float explosionForce, float explosionRadius, Vector3D<> position);
	~ExplosionForceGenerator();

	void UpdateForce(Particle* p, double t) override;

	void UpdateGenerator(double t);

	void AddShockWave(float speed);

private:
	float explosionForce;
	float explosionRadius;
	Vector3D<> position;
	std::list<ShockWave> shockWaveList;

	
};

