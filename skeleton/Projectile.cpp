#include "Projectile.h"

Projectile::Projectile(float realSpeed, float simulatedSpeed, float realMass, float realSize, Vector3D<> initialPosition, Vector3D<> direction) :
	Particle(initialPosition, direction * simulatedSpeed, physx::PxGeometryType::Enum::eSPHERE, realSize, physx::PxVec4(0.0, 0.0, 0.0, 1.0)),
	realSpeed(realSpeed),
	simulatedSpeed(simulatedSpeed),
	realMass(realMass)
{
	simulatedMass = CalculateSimulatedMass(this->realSpeed, this->simulatedSpeed, this->realMass);
	simulatedGravity = CalculateSimulatedGravity(this->realSpeed, this->simulatedSpeed);

	Particle::SetAceleration(Vector3D<>(0.0f, simulatedGravity, 0.0f));

}

Projectile::Projectile(Vector3D<> realSpeed, Vector3D<> simulatedSpeed, float realMass, float realSize, Vector3D<> initialPosition) :
	Particle(initialPosition, simulatedSpeed, physx::PxGeometryType::Enum::eSPHERE, realSize, physx::PxVec4(1.0, 1.0, 1.0, 1.0)),
	realSpeed(realSpeed.GetMagnitude()),
	simulatedSpeed(simulatedSpeed.GetMagnitude()),
	realMass(realMass)
{
	simulatedMass = CalculateSimulatedMass(this->realSpeed, this->simulatedSpeed, this->realMass);
	simulatedGravity = CalculateSimulatedGravity(this->realSpeed, this->simulatedSpeed);

	Particle::SetAceleration(Vector3D<>(0.0f, simulatedGravity, 0.0f));
}


Projectile::~Projectile()
{
}

float Projectile::CalculateSimulatedMass(float realSpeed, float simulatedSpeed, float realMass) const
{
	return realMass * (pow(realSpeed, 2) / pow(simulatedSpeed, 2));
}

float Projectile::CalculateSimulatedGravity(float realSpeed, float simulatedSpeed) const
{
	return G * (pow(simulatedSpeed, 2) / pow(realSpeed, 2));
}

float Projectile::CalculateEnergy(float speed, float mass) const
{
	return pow(speed, 2) * mass;
}
