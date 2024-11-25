#include "Submarine.h"
#include <iostream>

using namespace physx;

Submarine::Submarine(physx::PxTransform transform, float m, PxPhysics* physics, PxScene* scene)
{
	
	rigidBody = physics->createRigidDynamic(transform);		// Definimos una posición

	rigidBody->setLinearVelocity({ 0, 0, 0 });								// Definimos velocidad lienal
	rigidBody->setAngularVelocity({ 0, 0, 0 });								// Definimos velocidad angular

	radius = 10;
	height = 50;
	mass = m;
	volume = 3.141592 * pow(radius, 2) * height * 2 + (4 / 3 * 3.141592 * pow(radius, 3));

	shape = CreateShape(PxCapsuleGeometry(radius, height));							// Definimos una forma
	rigidBody->attachShape(*shape);

	PxRigidBodyExt::updateMassAndInertia(*rigidBody, mass/volume);			// Definimos la distribución de masas

	scene->addActor(*rigidBody);

	// Pintar submarino
	RenderItem* renderSubmarino;
	renderSubmarino = new RenderItem(shape, rigidBody, { 1, 1, 1, 1 });
}

void Submarine::UpdateBuoyancyForce(double t)
{
	float h = rigidBody->getGlobalPose().p.y;
	float h0 = 50;

	PxVec3 force(0, 0, 0);
	float immersed = 0.0;

	if (h - h0 > radius * 2 * 0.5) {
		immersed = 0.0;
	}
	else if (h - h0 < radius * 2 * 0.5) {
		// Totally immersed
		immersed = 1.0;
	}
	else {
		immersed = ((h0 - h) / (radius * 2)) + 0.5;
	}

	force.y = 0.15 * volume * immersed * 9.8;

	rigidBody->addForce(force * t);
	//rigidBody->addForce(rigidBody->getMass() * PxVec3(0, 9.8, 0));
	std::cout << rigidBody->getMass() << "\n";
}

void Submarine::UpdateGravityForce(double t)
{
	rigidBody->addForce(PxVec3(0, -9.8, 0) * mass * t );
}
