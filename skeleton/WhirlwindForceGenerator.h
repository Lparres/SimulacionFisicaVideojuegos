#pragma once
#include "WindForceGenerator.h"
class WhirlwindForceGenerator : public WindForceGenerator
{
public:
	WhirlwindForceGenerator(float windForce, float airFriction, Vector3D<> pos, float width);
	WhirlwindForceGenerator();

	void UpdateForce(Particle* p, double t) override;

	bool PositionOnWind(Vector3D<> pos) const;
};

