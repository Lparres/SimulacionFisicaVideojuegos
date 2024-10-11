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

	Vector3D<> GetAceleration() { return aceleration; }
	void SetAceleration(Vector3D<> acel) { aceleration = acel; }
	void SetVelocity(Vector3D<> vel) { velocity = vel; }
	void SetPosition(Vector3D<> pos) { tr->p = PxVec3(pos.x, pos.y, pos.z); }

protected: 
	RenderItem* item;
	Vector3D<> velocity;
	physx::PxTransform* tr;
	Vector3D<> aceleration;
	double damping;
};

