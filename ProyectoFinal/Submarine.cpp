#include "Submarine.h"
#include <iostream>

using namespace physx;

Submarine::Submarine(physx::PxTransform transform, float m, PxScene* scene)
{
	
	rigidBody = PxGetPhysics().createRigidDynamic(transform);		// Definimos una posición

	rigidBody->setLinearVelocity({ 0, 0, 0 });								// Definimos velocidad lienal
	rigidBody->setAngularVelocity({ 0, 0, 0 });								// Definimos velocidad angular
	
	baseMass = m;

	shape = CreateShape(PxCapsuleGeometry(radius, height));							// Definimos una forma
	rigidBody->attachShape(*shape);

	PxRigidBodyExt::updateMassAndInertia(*rigidBody, baseMass/volume);			// Definimos la distribución de masas

	scene->addActor(*rigidBody);

	// Pintar submarino
	RenderItem* renderSubmarino;
	renderSubmarino = new RenderItem(shape, rigidBody, { 0, 1.5, 0, 1 });

	movementDirection = PxVec3(0, 0, 0);

	main_BallastTank = BallastTank(20000, 2000);
	compensation_BallastTank = BallastTank(5000, 500);
	quick_BallastTank = BallastTank(8000, 4000);

}

void Submarine::UpdateForces(double t)
{
	UpdateBuoyancyForce(t);
	UpdateGravityForce(t);
	UpdateDragForce(t);
	UpdateMovementForce(t);

	std::cout << "Velocity: (" << rigidBody->getLinearVelocity().x << ", " << rigidBody->getLinearVelocity().y << ", " << rigidBody->getLinearVelocity().z << ")\n";

}

void Submarine::UpdateBallastTanks(double t)
{
	main_BallastTank.UpdateWaterVolume(t);
	compensation_BallastTank.UpdateWaterVolume(t);
	quick_BallastTank.UpdateWaterVolume(t);
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
}

void Submarine::UpdateGravityForce(double t)
{
	PxVec3 force(0, 0, 0);

	force.y = -9.8 * GetMass();

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
	PxVec3 force = movementDirection * GetMass();	// La fuerza del motor depende de la masa del submarino.
	rigidBody->addForce(force * t, physx::PxForceMode::eIMPULSE);
}

float Submarine::GetMass() const
{
	return  
		baseMass + 
		main_BallastTank.GetMass() +
		compensation_BallastTank.GetMass() +
		quick_BallastTank.GetMass(); 
}
