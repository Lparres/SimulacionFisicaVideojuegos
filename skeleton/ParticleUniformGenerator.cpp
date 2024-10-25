#include "ParticleUniformGenerator.h"
#include <cmath>
#include <array>
#include <random>

#define PI 3.14159265358979323846


ParticleUniformGenerator::ParticleUniformGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef) :
	ParticleGenerator(position, direction, speed, angleDelta, speedDelta, systemRef),
    uniformDist(-1, 1)
{}


ParticleUniformGenerator::~ParticleUniformGenerator()
{

}

void ParticleUniformGenerator::GenerateParticle()
{
    systemRef->AddParticle(position,
        RandomDir() * RandomSpeed(),
        physx::PxGeometryType::Enum::eSPHERE,
        0.5,
        physx::PxVec4(0.0, 1.0, 0.0, 1.0));
}

Vector3D<> ParticleUniformGenerator::RandomDir()
{
    // Genera un ángulo aleatorio entre -angleDelta y angleDelta (en radianes)
    float randomAngle = angleDelta * (PI / 180) * uniformDist(randomGen); // Ángulo en radianes

    // Genera un ángulo aleatorio en el plano (-π, π)
    float phi = uniformDist(randomGen) * PI;

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

    return result;
}

float ParticleUniformGenerator::RandomSpeed()
{
    // Genera una velocidad aleatoria entre -speedDelta y speedDelta
    float randomSpeed = speedDelta * uniformDist(randomGen);

    // Añade la nueva velocidad aleatoria a la original
    float result = randomSpeed + speed;

    return result;
}
