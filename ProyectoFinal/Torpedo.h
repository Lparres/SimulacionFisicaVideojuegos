#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Obstacle.h"
#include "ParticleSystem.h"
#include "Particle.h"

class Torpedo
{
public:
	Torpedo(physx::PxTransform transform, float m, physx::PxScene* scene, std::vector<Obstacle*>* obs, std::list<Particle*>& globalList);
	~Torpedo();

	physx::PxRigidDynamic* GetRigidBody() const { return rigidBody; };

	void UpdateForces(double t);

private:
	void UpdateMovementForce(double t);
	void CheckIfExplosion();

public:
	float GetDensity() const { return GetMass() / volume; }
	float GetMass() const { return baseMass; };
	float GetVolume() const { return volume; }

	physx::PxRigidDynamic* rigidBody;
	physx::PxShape* shape;

	physx::PxVec3 movementDirection;

private:
	const float radius = 2;
	const float height = 10;
	const float volume = 3.141592 * pow(radius, 2) * height * 2 + (4 / 3 * 3.141592 * pow(radius, 3));

	float baseMass;

	physx::PxVec3 lastVelocity;

	std::vector<Obstacle*>* obstacles;

	ParticleSystem* particleSystem = nullptr;
};

