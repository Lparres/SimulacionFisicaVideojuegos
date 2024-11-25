#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Submarine
{
public:
	Submarine(physx::PxTransform transform, float m, physx::PxPhysics* physics, physx::PxScene* scene);

	physx::PxRigidDynamic* GetRigidBody() const { return rigidBody; };

	void UpdateBuoyancyForce(double t);
	void UpdateGravityForce(double t);
private:
	physx::PxRigidDynamic* rigidBody;

	physx::PxShape* shape;
	float radius;
	float height;
	float mass;
	float volume;

	RenderItem* renderItem;
};

