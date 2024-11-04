#pragma once
#include "Vector3D.h"
#include <PxPhysicsAPI.h>
#include <list>
#include <vector>

class RenderItem;
class ForceGenerator;

class Particle
{
public:
	Particle::Particle(std::list<Particle*>& globalList,
					   Vector3D<> position, 
					   Vector3D<> velocity, 
					   float mass = 1,
					   const physx::PxGeometryType::Enum& geoType = physx::PxGeometryType::Enum::eSPHERE, 
					   float size = 1, 
					   const physx::PxVec4& color = physx::PxVec4(1.0, 1.0, 0.0, 1.0));
	~Particle();

	void Integrate(double t);
	void UpdateState(double t);

	double GetLifeTime() { return lifeTime; };

	Vector3D<> GetAceleration() const { return aceleration; }
	Vector3D<> GetVelocity() const { return velocity; };
	Vector3D<> GetPosition() const { return Vector3D<>(tr->p.x, tr->p.y, tr->p.z); };
	float GetMass() const { return mass; };
	void SetAceleration(Vector3D<> acel) { aceleration = acel; }
	void SetVelocity(Vector3D<> vel) { velocity = vel; }
	void SetPosition(Vector3D<> pos) { tr->p = physx::PxVec3(pos.x, pos.y, pos.z); }
	void SetMass(float m) { mass = m; };
	
	void AddForceGenerator(ForceGenerator* fg);

	void ApplyInstantForce(Vector3D<> f);
	void ApplyContinuousForce(Vector3D<> f);

protected: 
	RenderItem* renderItem;

	physx::PxTransform* tr;
	Vector3D<> velocity;
	Vector3D<> aceleration;

	float mass;

	double damping;

	double lifeTime;

	std::list<Particle*>& globalListRef;
	std::list<Particle*>::iterator myIt;

	std::vector<ForceGenerator*> forceGenerators;
};

