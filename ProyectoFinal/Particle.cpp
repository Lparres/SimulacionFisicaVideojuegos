#include "Particle.h"

#include "ForceGenerator.h"
#include "RenderUtils.hpp"
#include <cmath>
#include <limits>

using namespace physx;

Particle::Particle(std::list<Particle*>& globalList, Vector3D<> pos, Vector3D<> vel, float m, const PxGeometryType::Enum& geoType, float size, const PxVec4& color) :
	globalListRef(globalList)
{
	globalListRef.push_back(this);
	myIt = std::prev(globalListRef.end());
	tr = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	velocity = vel;
	aceleration = Vector3D<>();
	mass = m;
	damping = 0.995;
	PxShape* shape = nullptr;
	lifeTime = 0;

	switch (geoType)
	{
	case PxGeometryType::Enum::eSPHERE:
		shape = CreateShape(PxSphereGeometry(size));
		break;
	case PxGeometryType::Enum::ePLANE:
		shape = CreateShape(PxPlaneGeometry());
		break;
	case PxGeometryType::Enum::eCAPSULE:
		shape = CreateShape(PxCapsuleGeometry(size, size));
		break;
	case PxGeometryType::Enum::eBOX:
		shape = CreateShape(PxBoxGeometry(size, size, size));
		break;
	default:
		break;
	}

	renderItem = new RenderItem(shape, tr, color);
}

// For plane (buoyancy)
Particle::Particle(std::list<Particle*>& globalList, Vector3D<> position, float sizeX, float sizeZ, const physx::PxVec4& color) :
	globalListRef(globalList)
{
	globalListRef.push_back(this);
	myIt = std::prev(globalListRef.end());
	tr = new PxTransform(PxVec3(position.x, position.y, position.z));

	velocity = Vector3D<>();
	aceleration = Vector3D<>();
	mass = -10000;
	damping = 0;
	lifeTime = -10000;

	renderItem = new RenderItem(CreateShape(PxBoxGeometry(sizeX, 0.1, sizeZ)), tr, color);
}

Particle::~Particle()
{
	globalListRef.erase(myIt);
	DeregisterRenderItem(renderItem);
	delete renderItem;
	delete tr;
}

void Particle::Integrate(double t)
{
	// Euler Semi-Implicito

	velocity = velocity * std::pow(damping, t); // Damping

	velocity = velocity + aceleration * t; // Aceleración

	tr->p += PxVec3(velocity.x, velocity.y, velocity.z) * t; // Seteamos posicion	
}

void Particle::UpdateState(double t)
{
	for (auto fg : forceGenerators) {
		fg->UpdateForce(this, t);
	}

	lifeTime += t;
}

void Particle::AddForceGenerator(ForceGenerator* fg)
{
	forceGenerators.push_back(fg);
}

void Particle::ApplyInstantForce(Vector3D<> f)
{
	velocity = velocity + f / mass;
}

void Particle::ApplyContinuousForce(Vector3D<> f)
{
	aceleration = aceleration + f / mass;
}
