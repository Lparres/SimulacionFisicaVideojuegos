#pragma once

#include "ParticleGenerator.h"


class ParticleUniformGenerator : public ParticleGenerator
{
public:
	ParticleUniformGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef);
	~ParticleUniformGenerator();

private:

	void GenerateParticle() override;
	Vector3D<> RandomDir();
	float RandomSpeed();


	std::uniform_real_distribution<> uniformDist;
};

