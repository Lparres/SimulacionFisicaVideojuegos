#include "ParticleNormalGenerator.h"
#include <cmath>
#include <array>
#include <random>

#define PI 3.14159265358979323846;


ParticleNormalGenerator::ParticleNormalGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef) :
	ParticleGenerator(position, direction, speed, angleDelta, speedDelta, systemRef)
{}


ParticleNormalGenerator::~ParticleNormalGenerator()
{

}

void ParticleNormalGenerator::GenerateParticle()
{

    // Genera un ángulo aleatorio entre 0 y angle (en radianes)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    float randomAngle = angleDelta * dis(gen); // Ángulo en radianes

    // Genera un ángulo aleatorio en el plano (0, 2π)
    float phi = dis(gen) * 2 * PI;

    // Calcula las coordenadas del nuevo vector
    float sinRandomAngle = std::sin(randomAngle);
    float cosRandomAngle = std::cos(randomAngle);

    // Vector en coordenadas esféricas
    Vector3D<> randomVector = {
        sinRandomAngle * std::cos(phi),
        sinRandomAngle * std::sin(phi),
        cosRandomAngle
    };

    // Combina el nuevo vector con la dirección
    // Proyección en la dirección del vector
    Vector3D<> result = {
        direction.x * cosRandomAngle + randomVector.x,
        direction.y * cosRandomAngle + randomVector.y,
        direction.z * cosRandomAngle + randomVector.z
    };

    // Normaliza el resultado
    result.Normalize();

	systemRef->AddParticle(position, result * speed);
}
