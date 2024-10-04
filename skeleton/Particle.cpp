#include "Particle.h"

#include "RenderUtils.hpp"
#include <cmath>

using namespace physx;

Particle::Particle(Vector3D<> pos, Vector3D<> vel, const PxGeometryType::Enum& geoType, float size, const PxVec4& color)
{
	tr = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	velocity = vel;
	aceleration = Vector3D<>();
	damping = 1;
	PxShape* shape = nullptr;

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

	item = new RenderItem(shape, tr, color);
}

Particle::~Particle()
{
	DeregisterRenderItem(item);
	delete item;
	delete tr;
}

void Particle::Integrate(double t)
{
	// Euler Semi-Implicito

	velocity = velocity * std::pow(damping, t); // Damping

	velocity = velocity + aceleration * t; // Aceleración

	tr->p += PxVec3(velocity.x, velocity.y, velocity.z) * t; // Seteamos posicion

	std::cout << velocity;
	
}
