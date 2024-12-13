#include "Torpedo.h"
#include <iostream>

using namespace physx;

Torpedo::Torpedo(physx::PxTransform transform, float m, physx::PxScene* scene, std::vector<Obstacle*>* obs)
{
	rigidBody = PxGetPhysics().createRigidDynamic(transform);		// Definimos una posición

	rigidBody->setLinearVelocity({ 0, 0, 0 });								// Definimos velocidad lienal
	rigidBody->setAngularVelocity({ 0, 0, 0 });								// Definimos velocidad angular

	baseMass = m;

	shape = CreateShape(PxCapsuleGeometry(radius, height));							// Definimos una forma
	rigidBody->attachShape(*shape);

	PxRigidBodyExt::updateMassAndInertia(*rigidBody, baseMass / volume);			// Definimos la distribución de masas

	scene->addActor(*rigidBody);

	// Pintar torpedo
	RenderItem* renderTorpedo;
	renderTorpedo = new RenderItem(shape, rigidBody, { 5, 2, 0, 1 });

	movementDirection = PxVec3(0, 0, 0);

	obstacles = obs;
	lastVelocity = PxVec3(0, 0, 0);
}

void Torpedo::UpdateForces(double t)
{
	UpdateMovementForce(t);
	CheckIfExplosion();
}

void Torpedo::UpdateMovementForce(double t)
{
	PxVec3 force = movementDirection * GetMass();	// La fuerza del motor depende de la masa del submarino.
	rigidBody->addForce(force * t, physx::PxForceMode::eIMPULSE);
}

void Torpedo::CheckIfExplosion()
{
	if (abs(lastVelocity.magnitude()) > abs(rigidBody->getLinearVelocity().magnitude())) {
		std::cout << "IMPACTO" << "\n";
		for (auto e : *obstacles) {
			e->Explode(rigidBody->getGlobalPose().p);
		}
		rigidBody->setGlobalPose(PxTransform(PxVec3(0, 1000, 0)));
	}

	lastVelocity = rigidBody->getLinearVelocity();

}
