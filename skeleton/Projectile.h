#pragma once

#include "Particle.h"

#define G -9.81

class Projectile : public Particle
{

public:

	Projectile(std::list<Particle*>& globalList, float realSpeed, float simulatedSpeed, float realMass, float realSize, Vector3D<> initialPosition, Vector3D<> direction);
	Projectile(std::list<Particle*>& globalList, Vector3D<> realSpeed, Vector3D<> simulatedSpeed, float realMass, float realSize, Vector3D<> initialPosition);
	~Projectile();

	float CalculateEnergy(float speed, float mass) const;

private:

	float CalculateSimulatedMass(float realSpeed, float simulatedSpeed, float realMass) const;
	float CalculateSimulatedGravity(float realSpeed, float simulatedSpeed) const;

	float realSpeed;
	float simulatedSpeed;
	float realMass;
	float simulatedMass;

	float simulatedGravity;
};

