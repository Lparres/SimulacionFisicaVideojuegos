#pragma once
#include "ParticleGenerator.h"
class ParticleNormalGenerator : public ParticleGenerator
{
public:
	ParticleNormalGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef);
	~ParticleNormalGenerator();

private:
	void GenerateParticle() override;
};

