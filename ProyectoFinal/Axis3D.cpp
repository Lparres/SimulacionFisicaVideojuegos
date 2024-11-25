#include "Axis3D.h"

#include <PxPhysicsAPI.h>

#include "RenderUtils.hpp"
#include "Vector3D.h"

using namespace physx;

Axis3D::Axis3D() {

	Vector3D<> const vX(10, 0, 0);
	Vector3D<> const vY(0, 10, 0);
	Vector3D<> const vZ(0, 0, 10);
	Vector3D<> const vO(0, 0, 0);

	PxShape* shape = CreateShape(PxSphereGeometry(1));

	ballX = new RenderItem(shape, 
						   new PxTransform(PxVec3(vX.x, vX.y, vX.z)),
						   PxVec4(1.0, 0.0, 0.0, 1.0));

	ballY = new RenderItem(shape,
						   new PxTransform(PxVec3(vY.x, vY.y, vY.z)),
						   PxVec4(0.0, 1.0, 0.0, 1.0));

	ballZ = new RenderItem(shape,
						   new PxTransform(PxVec3(vZ.x, vZ.y, vZ.z)),
						   PxVec4(0.0, 0.0, 1.0, 1.0));

	ballO = new RenderItem(shape,
						   new PxTransform(PxVec3(vO.x, vO.y, vO.z)),
						   PxVec4(1.0, 1.0, 1.0, 1.0));
}

Axis3D::~Axis3D() {
	DeregisterRenderItem(ballX);
	DeregisterRenderItem(ballY);
	DeregisterRenderItem(ballZ);
	DeregisterRenderItem(ballO);
	delete ballX;
	delete ballY;
	delete ballZ;
	delete ballO;
}