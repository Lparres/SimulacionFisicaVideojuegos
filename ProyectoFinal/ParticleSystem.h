#pragma once

#include <list>
#include "Vector3D.h"
#include <PxPhysicsAPI.h>

#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "BuoyancyForceGenerator.h"

class ParticleGenerator;
class Particle;

#define MAX_DISTANCE 2000
#define MAX_LIFETIME 100

class ParticleSystem
{
public:
	ParticleSystem(std::list<Particle*>& globalList);
	~ParticleSystem();

	int AddUniformGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta);
	int AddGaussianGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta);
	int AddRainGenerator(Vector3D<> position, float radius, int intensity);

	void AddParticle(Vector3D<> position,
					 Vector3D<> velocity,
					 float mass,
					 const physx::PxGeometryType::Enum& geoType = physx::PxGeometryType::Enum::eSPHERE,
					 float size = 1,
					 const physx::PxVec4& color = physx::PxVec4(1.0, 1.0, 0.0, 1.0));

	void Update(double t);

	void Explode();

	void Generate2ParticleSpring();
	void GenerateAnchoredSpring();

	void GenerateBuoyancyDemo();

private:
	std::list<ParticleGenerator*> generators;
	std::list<Particle*> particles;
	std::list<Particle*>& globalListRef;

	std::list<ForceGenerator*> otherGenerators;

	GravityForceGenerator* gravityForceGenerator;
	WindForceGenerator* windForceGenerator;
	WhirlwindForceGenerator* whirlwindForceGenerator;
	ExplosionForceGenerator* explosionForceGenerator;

	void GenerateParticles();
	void KillParticles();
	void UpdateParticles(double t);
};

