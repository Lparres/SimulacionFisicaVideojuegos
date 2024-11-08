#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(float explosionForce, float explosionRadius, Vector3D<> position) :
	ForceGenerator(),
	explosionForce(explosionForce),
	explosionRadius(explosionRadius),
	position(position)
{
}

ExplosionForceGenerator::~ExplosionForceGenerator()
{

}

void ExplosionForceGenerator::UpdateForce(Particle* p, double t)
{
	Vector3D<> dir = p->GetPosition() - position;
	float distance = dir.GetMagnitude();
	if (distance < explosionRadius) {
		p->ApplyInstantForce(dir * (explosionForce / pow(distance, 2)));
	}
}