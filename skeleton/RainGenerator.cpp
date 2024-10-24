#include "RainGenerator.h"

#define PI 3.14159265358979323846

RainGenerator::RainGenerator(Vector3D<> position, float radius, int intensity, ParticleSystem* systemRef) :
	ParticleGenerator(position, Vector3D<>(0, -1, 0), 0, 0, 0, systemRef),
	radius(radius),
	intensity(intensity)
{

}

RainGenerator::~RainGenerator()
{
}

void RainGenerator::GenerateParticle()
{
	std::cout << "hola";
	for(int i = 0; i < intensity; i++)
		systemRef->AddParticle(CalculateRandomPos(), Vector3D<>(0, -1, 0));
}

Vector3D<> RainGenerator::CalculateRandomPos()
{
	std::uniform_real_distribution<> uniformDist(-1, 1);
	std::uniform_real_distribution<> angleDist(-PI, PI);

	float randomRadius = radius * sqrt(uniformDist(randomGen));
	float randomAngle = angleDist(randomGen);

	float xCoord = randomRadius * std::cos(randomAngle);
	float zCoord = randomRadius * std::sin(randomAngle);

	Vector3D<> result = {
		xCoord + position.x,
		position.y,
		zCoord + position.z
	};

	return result;
}
