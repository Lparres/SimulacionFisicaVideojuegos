#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"


class Submarine
{
public:
	Submarine(physx::PxTransform transform, float m, physx::PxPhysics* physics, physx::PxScene* scene);

	physx::PxRigidDynamic* GetRigidBody() const { return rigidBody; };

	void UpdateForces(double t);

private:
	void UpdateBuoyancyForce(double t);
	void UpdateGravityForce(double t);
	void UpdateDragForce(double t);
	void UpdateMovementForce(double t);

public:
	 float GetDensity() const { return mass / volume; }
	 float GetMass() const { return mass; }
	 float GetVolume() const { return volume; }

	 void SetMass(float newMass) { mass = newMass; }
	 void ChangeMass(float massDiff) { mass += massDiff; }

	physx::PxRigidDynamic* rigidBody;
	physx::PxShape* shape;

	const float radius = 10;
	const float height = 50;
	const float volume = 3.141592 * pow(radius, 2) * height * 2 + (4 / 3 * 3.141592 * pow(radius, 3));

	float mass;

	RenderItem* renderItem;

	physx::PxVec3 movementDirection;
};

