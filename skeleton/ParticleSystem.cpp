#include "ParticleSystem.h"
#include "ParticleGaussianGenerator.h"
#include "ParticleNormalGenerator.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}


int ParticleSystem::AddNormalGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta)
{
	ParticleGenerator* generator = new ParticleNormalGenerator(position, direction, speed, angleDelta, speedDelta, this);
	generator->SetID(generators.size());
	generators.push_back(generator);
	return generator->GetID();
}

int ParticleSystem::AddGaussianGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta)
{
	ParticleGenerator* generator = new ParticleGaussianGenerator(position, direction, speed, angleDelta, speedDelta, this);
	generator->SetID(generators.size());
	generators.push_back(generator);
	return generator->GetID();
}

void ParticleSystem::AddParticle(Vector3D<> position, Vector3D<> velocity)
{
	particles.push_back(new Particle(position, velocity));
}

void ParticleSystem::Update(double t)
{
	GenerateParticles();
	KillParticles();
	UpdateParticles(t);
}

void ParticleSystem::GenerateParticles()
{
	for (ParticleGenerator* gen : generators) {
		gen->GenerateParticle();
	}
}

void ParticleSystem::KillParticles()
{
	for (auto it = particles.begin(); it != particles.end(); ) {
		if ((*it)->GetPosition().GetMagnitude() > MAX_DISTANCE) {
			delete* it;
			it = particles.erase(it); // borra y avanza el iterador
		}
		else {
			++it; // solo avanza el iterador si no se borró el elemento
		}
	}
}

void ParticleSystem::UpdateParticles(double t)
{
	for (Particle* p : particles) {
		p->Integrate(t);
	}
}
