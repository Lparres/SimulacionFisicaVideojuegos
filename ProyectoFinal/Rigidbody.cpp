#include "Rigidbody.h"

using namespace physx;

Rigidbody::Rigidbody(physx::PxTransform transform, float m, physx::PxScene* scene)
{
	rigidBody = PxGetPhysics().createRigidDynamic(transform);		// Definimos una posición

	rigidBody->setLinearVelocity({ 0, 0, 0 });								// Definimos velocidad lienal
	rigidBody->setAngularVelocity({ 0, 0, 0 });

	scene->addActor(*rigidBody);

	baseMass = m;
}

void Rigidbody::UpdateForces(double t)
{
	//UpdateBuoyancyForce(t);
	//UpdateGravityForce(t);
	//UpdateDragForce(t);
	//UpdateMovementForce(t);
}