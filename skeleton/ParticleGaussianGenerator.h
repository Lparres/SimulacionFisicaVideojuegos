#pragma once
#include "ParticleGenerator.h"
class ParticleGaussianGenerator : public ParticleGenerator
{
public:
	ParticleGaussianGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef);
	~ParticleGaussianGenerator();

private:
	void GenerateParticle() override;
	Vector3D<> RandomDir();
	float RandomSpeed();


	std::normal_distribution<> gaussianDistAngle;
	std::normal_distribution<> gaussianDistSpeed;
};

