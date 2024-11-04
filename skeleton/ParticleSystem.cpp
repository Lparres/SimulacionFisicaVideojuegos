#include "ParticleSystem.h"
#include "ParticleGaussianGenerator.h"
#include "ParticleUniformGenerator.h"
#include "RainGenerator.h"
#include "GravityForceGenerator.h"

ParticleSystem::ParticleSystem(std::list<Particle*>& globalList) :
	globalListRef(globalList)
{
}

ParticleSystem::~ParticleSystem()
{
}


int ParticleSystem::AddUniformGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta)
{
	ParticleGenerator* generator = new ParticleUniformGenerator(position, direction, speed, angleDelta, speedDelta, this);
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

int ParticleSystem::AddRainGenerator(Vector3D<> position, float radius, int intensity)
{
	ParticleGenerator* generator = new RainGenerator(position, radius, intensity, this);
	generator->SetID(generators.size());
	generators.push_back(generator);
	return generator->GetID();
}

void ParticleSystem::AddParticle(Vector3D<> position, Vector3D<> velocity, float mass, const physx::PxGeometryType::Enum& geoType, float size, const physx::PxVec4& color)
{
	Particle* p = new Particle(globalListRef, position, velocity, mass, geoType, size, color);
	p->AddForceGenerator(new GravityForceGenerator(Vector3D<>(0, -9.8, 0)));
	particles.push_back(p);
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
		if ((*it)->GetPosition().GetMagnitude() > MAX_DISTANCE || (*it)->GetLifeTime() > MAX_LIFETIME) {
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
		p->UpdateState(t);
	}
}
