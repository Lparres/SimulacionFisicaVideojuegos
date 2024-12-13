#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Rigidbody
{
public:
	Rigidbody(physx::PxTransform transform, float m, physx::PxScene* scene);
	
	physx::PxRigidDynamic* GetRigidBody() const { return rigidBody; };

	void UpdateForces(double t);

protected:
	void UpdateBuoyancyForce(double t);
	void UpdateGravityForce(double t);
	void UpdateDragForce(double t);
	void UpdateMovementForce(double t);

protected:
	physx::PxRigidDynamic* rigidBody;

	float baseMass;
};

