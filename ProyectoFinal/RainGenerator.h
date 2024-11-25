#pragma once
#include "ParticleGenerator.h"

class RainGenerator : public ParticleGenerator
{
public:
	RainGenerator(Vector3D<> position, float radius, int intensity, ParticleSystem* systemRef);
	~RainGenerator();

private:
	void GenerateParticle() override;

	Vector3D<> CalculateRandomPos();

	float radius;
	int intensity;
};

