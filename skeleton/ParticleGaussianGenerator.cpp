#include "ParticleGaussianGenerator.h"
#include <limits>

#define PI 3.14159265358979323846

ParticleGaussianGenerator::ParticleGaussianGenerator(Vector3D<> position, Vector3D<> direction, float speed, float angleDelta, float speedDelta, ParticleSystem* systemRef) :
	ParticleGenerator(position, direction, speed, angleDelta, speedDelta, systemRef)
{
    if (angleDelta != 0.0) 
        gaussianDistAngle = std::normal_distribution<>(0, angleDelta * (PI / 180));
    else
        gaussianDistAngle = std::normal_distribution<>(0, std::numeric_limits<float>::min());


    if (speedDelta != 0.0)
        gaussianDistSpeed = std::normal_distribution<>(0, speedDelta);
    else
        gaussianDistSpeed = std::normal_distribution<>(0, std::numeric_limits<float>::min());
}


ParticleGaussianGenerator::~ParticleGaussianGenerator()
{

}

void ParticleGaussianGenerator::GenerateParticle()
{
    systemRef->AddParticle(position,
        RandomDir() * RandomSpeed(),
        1,
        physx::PxGeometryType::Enum::eSPHERE,
        0.5,
        physx::PxVec4(1.0, 1.0, 0.0, 1.0));
}

Vector3D<> ParticleGaussianGenerator::RandomDir()
{
    // Genera un ángulo aleatorio entre -angleDelta y angleDelta (en radianes)
    float randomAngle = gaussianDistAngle(randomGen); // Ángulo en radianes

    // Genera un ángulo aleatorio en el plano (-π, π)
    float phi = gaussianDistAngle(randomGen) * PI;

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

float ParticleGaussianGenerator::RandomSpeed()
{
    // Genera una velocidad aleatoria entre -speedDelta y speedDelta
    float randomSpeed = gaussianDistSpeed(randomGen);

    // Añade la nueva velocidad aleatoria a la original
    float result = randomSpeed + speed;

    return result;
}
