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
	for (ShockWave sw : shockWaveList) {
		if (distance < sw.radius) {
			p->ApplyInstantForce(dir * (explosionForce / pow(distance, 2)) * pow(2.71828, -sw.time/0.1));
		}
	}
}

void ExplosionForceGenerator::UpdateGenerator(double t)
{
	for (auto it = shockWaveList.begin(); it != shockWaveList.end(); ) {
		it->time += t;
		it->radius = it->speed * it->time;

		if (it->radius > explosionRadius)
			it = shockWaveList.erase(it);
		else
			++it;
	}
}

void ExplosionForceGenerator::AddShockWave(float speed)
{
	shockWaveList.emplace_back(0, speed, 0);
}
