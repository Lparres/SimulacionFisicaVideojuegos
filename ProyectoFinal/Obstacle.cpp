#include "Obstacle.h"
#include <iostream>

using namespace physx;

Obstacle::Obstacle(physx::PxVec3 size, physx::PxTransform transform, float m, physx::PxScene* scene)
{
	rigidBody = PxGetPhysics().createRigidDynamic(transform);		// Definimos una posición
	baseMass = m;
	volume = size.x * size.y * size.z;

	shape = CreateShape(PxBoxGeometry(size.x, size.y, size.z));							// Definimos una forma
	rigidBody->attachShape(*shape);

	PxRigidBodyExt::updateMassAndInertia(*rigidBody, baseMass / volume);			// Definimos la distribución de masas

	scene->addActor(*rigidBody);

	// Pintar obstáculo
	RenderItem* renderObstacle;
	renderObstacle = new RenderItem(shape, rigidBody, { 2, 0, 0, 1 });

}

void Obstacle::UpdateForces(double t)
{
	UpdateGravityForce(t);
	UpdateDragForce(t);
}

void Obstacle::Explode(physx::PxVec3 origin)
{
	PxVec3 dir = rigidBody->getGlobalPose().p - origin;
	float distance = dir.magnitude();
	if (distance < 1000) {
		std::cout << "Dir.Y: " << dir.y << "\n";
		rigidBody->addForce(dir * (500000 / pow(distance, 2)), physx::PxForceMode::eIMPULSE);
	}
		
}

void Obstacle::UpdateGravityForce(double t)
{
	PxVec3 force(0, 0, 0);
	force.y = -50 * baseMass;
	rigidBody->addForce(force * t, physx::PxForceMode::eIMPULSE);
}

void Obstacle::UpdateDragForce(double t)
{
	PxVec3 force = -1 * rigidBody->getLinearVelocity() * baseMass * 0.1; // Aproximación de la fuerza de rozamiento
	rigidBody->addForce(force * t, physx::PxForceMode::eIMPULSE);
}
