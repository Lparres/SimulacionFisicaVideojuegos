#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "BallastTank.h"


class Submarine
{
public:
	Submarine(physx::PxTransform transform, float m, physx::PxPhysics* physics, physx::PxScene* scene);

	physx::PxRigidDynamic* GetRigidBody() const { return rigidBody; };

	void UpdateForces(double t);

	void UpdateBallastTanks(double t);

private:
	void UpdateBuoyancyForce(double t);
	void UpdateGravityForce(double t);
	void UpdateDragForce(double t);
	void UpdateMovementForce(double t);

public:
	 float GetDensity() const { return GetMass() / volume; }
	 float GetMass() const;
	 float GetVolume() const { return volume; }

	 void SetBaseMass(float newMass) { baseMass = newMass; }
	 void ChangeBaseMass(float massDiff) { baseMass += massDiff; }

	physx::PxRigidDynamic* rigidBody;
	physx::PxShape* shape;

private:
	const float radius = 10;
	const float height = 50;
	const float volume = 3.141592 * pow(radius, 2) * height * 2 + (4 / 3 * 3.141592 * pow(radius, 3));

	float baseMass;
public:
	BallastTank main_BallastTank;
	BallastTank compensation_BallastTank;
	BallastTank quick_BallastTank;


	RenderItem* renderItem;

	physx::PxVec3 movementDirection;
};

