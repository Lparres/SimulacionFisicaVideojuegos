#pragma once
#include "Vector3D.h"
#include <PxPhysicsAPI.h>

class RenderItem;

class Particle
{
public:
	Particle::Particle(Vector3D<> position, 
					   Vector3D<> velocity, 
					   const physx::PxGeometryType::Enum& geoType = physx::PxGeometryType::Enum::eSPHERE, 
					   float size = 1, 
					   const physx::PxVec4& color = physx::PxVec4(1.0, 1.0, 0.0, 1.0));
	~Particle();

	void Integrate(double t);

private: 
	RenderItem* item;
	Vector3D<> velocity;
	physx::PxTransform* tr;
};

