#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"


class Obstacle
{
public:
	Obstacle(physx::PxVec3 size, physx::PxTransform transform, float m, physx::PxScene* scene);

	void UpdateForces(double t);
	void Explode(physx::PxVec3 origin);

private:
	void UpdateGravityForce(double t);
	void UpdateDragForce(double t);
	

public:
	physx::PxRigidDynamic* rigidBody;
	physx::PxShape* shape;

private:
	float baseMass;
	float volume;

};

