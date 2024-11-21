#include "ParticleSystem.h"
#include "ParticleGaussianGenerator.h"
#include "ParticleUniformGenerator.h"
#include "RainGenerator.h"


ParticleSystem::ParticleSystem(std::list<Particle*>& globalList) :
	globalListRef(globalList)
{
	gravityForceGenerator = new GravityForceGenerator(Vector3D<>(0, -9.8, 0));
	windForceGenerator = new WindForceGenerator(Vector3D<>(0, 1, 0), 0, 0.5, Vector3D<>(0, 0, 0), 1000);
	whirlwindForceGenerator = new WhirlwindForceGenerator(1, 0.5, Vector3D<>(0, 0, 0), 1000);
	explosionForceGenerator = new ExplosionForceGenerator(500, 1000, Vector3D<>(0, 0, 10));
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
	
	p->AddForceGenerator(gravityForceGenerator);
	//p->AddForceGenerator(windforceGenerator);
	//p->AddForceGenerator(whirlwindForceGenerator);
	p->AddForceGenerator(explosionForceGenerator);
	particles.push_back(p);
}


void ParticleSystem::Update(double t)
{
	explosionForceGenerator->UpdateGenerator(t);

	GenerateParticles();
	KillParticles();
	UpdateParticles(t);
}

void ParticleSystem::Explode()
{
	explosionForceGenerator->AddShockWave(1000);
}

void ParticleSystem::Generate2ParticleSpring()
{
	Particle* p1 = new Particle(globalListRef, Vector3D<>(-10, 0, 0), Vector3D<>(0, 0, 0), 1, physx::PxGeometryType::Enum::eSPHERE, 1, physx::PxVec4(0.0, 1.0, 1.0, 1.0));
	Particle* p2 = new Particle(globalListRef, Vector3D<>(10, 0, 0), Vector3D<>(0, 0, 0), 1, physx::PxGeometryType::Enum::eSPHERE, 1, physx::PxVec4(1.0, 0.0, 1.0, 1.0));

	SpringForceGenerator* fg1 = new SpringForceGenerator(1, 10, p2);
	SpringForceGenerator* fg2 = new SpringForceGenerator(1, 10, p1);

	p1->AddForceGenerator(fg1);
	p2->AddForceGenerator(fg2);

	particles.push_back(p1);
	particles.push_back(p2);
	otherGenerators.push_back(fg1);
	otherGenerators.push_back(fg2);
}

void ParticleSystem::GenerateAnchoredSpring()
{
	Particle* p = new Particle(globalListRef, Vector3D<>(-10, 0, 0), Vector3D<>(0, 0, 0), 1, physx::PxGeometryType::Enum::eSPHERE, 1, physx::PxVec4(0.0, 1.0, 1.0, 1.0));
	AnchoredSpringFG* fg = new AnchoredSpringFG(globalListRef, 1, 10, Vector3D<>(10, 0, 0));

	p->AddForceGenerator(fg);

	particles.push_back(p);
	otherGenerators.push_back(fg);
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
