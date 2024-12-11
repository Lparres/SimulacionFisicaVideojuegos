#include "Submarine.h"
#include <iostream>

using namespace physx;

Submarine::Submarine(physx::PxTransform transform, float m, PxPhysics* physics, PxScene* scene)
{
	
	rigidBody = physics->createRigidDynamic(transform);		// Definimos una posición

	rigidBody->setLinearVelocity({ 0, 0, 0 });								// Definimos velocidad lienal
	rigidBody->setAngularVelocity({ 0, 0, 0 });								// Definimos velocidad angular
	
	mass = m;

	shape = CreateShape(PxCapsuleGeometry(radius, height));							// Definimos una forma
	rigidBody->attachShape(*shape);

	PxRigidBodyExt::updateMassAndInertia(*rigidBody, mass/volume);			// Definimos la distribución de masas

	scene->addActor(*rigidBody);

	// Pintar submarino
	RenderItem* renderSubmarino;
	renderSubmarino = new RenderItem(shape, rigidBody, { 1, 1, 1, 1 });

	movementDirection = PxVec3(0, 0, 0);
}

void Submarine::UpdateForces(double t)
{
	UpdateBuoyancyForce(t);
	UpdateGravityForce(t);
	UpdateDragForce(t);
	UpdateMovementForce(t);
}

void Submarine::UpdateBuoyancyForce(double t)
{
	float h = rigidBody->getGlobalPose().p.y;
	float h0 = 50;

	PxVec3 force(0, 0, 0);
	float immersed = 0.0;

	if (h - h0 > radius) {
		immersed = 0.0;
	}
	else if (h - h0 < radius * -1) {
		// Totally immersed
		immersed = 1.0;
	}
	else {
		immersed = ((h0 - h) / (radius * 2)) + 0.5;
	}

	force.y = 1 * volume * immersed * 9.8;	// Liquid density * displaced volume * gravity aceleration

	rigidBody->addForce(force * t, physx::PxForceMode::eIMPULSE);
	//rigidBody->addForce(rigidBody->getMass() * PxVec3(0, 9.8, 0));
	//std::cout << "Fuerza de flotacion: " << force.y << "\n";
	std::cout << "Velocity: " << rigidBody->getLinearVelocity().x << "\n";
}

void Submarine::UpdateGravityForce(double t)
{
	PxVec3 force(0, 0, 0);

	force.y = -9.8 * mass;

	rigidBody->addForce(force * t, physx::PxForceMode::eIMPULSE);
	//std::cout << "Fuerza de gravedad: " << -9.8 * mass << "\n";

}

void Submarine::UpdateDragForce(double t)
{
	PxVec3 force = -1 * rigidBody->getLinearVelocity() * volume * 0.3; // Aproximación de la fuerza de rozamiento
	rigidBody->addForce(force * t, physx::PxForceMode::eIMPULSE);
}

void Submarine::UpdateMovementForce(double t)
{
	PxVec3 force = movementDirection * mass;	// La fuerza del motor depende de la masa del submarino.
	rigidBody->addForce(force * t, physx::PxForceMode::eIMPULSE);
}
