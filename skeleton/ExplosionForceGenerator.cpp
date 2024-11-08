#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(float explosionForce, float explosionRadius, Vector3D<> position) :
	ForceGenerator(),
	explosionForce(explosionForce),
	explosionRadius(explosionRadius),
	position(position),
	explosionActive(false)
{
}

ExplosionForceGenerator::~ExplosionForceGenerator()
{
}

void ExplosionForceGenerator::UpdateForce(Particle* p, double t)
{
	if (explosionActive) {
		Vector3D<> dir = p->GetPosition() - position;
		float distance = dir.GetMagnitude();
		if (distance < explosionRadius) {
			p->ApplyInstantForce(dir * (explosionForce / pow(distance, 2)));
		}
		explosionActive = false;
	}
}

// Function called when a key is pressed
void ExplosionForceGenerator::keyPress(unsigned char key, const physx::PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{
		//case 'B': break;
		//case ' ':	break;
	case 'E':
	{

		std::cout << "ola";
		break;
	}
	default:
		break;
	}
}