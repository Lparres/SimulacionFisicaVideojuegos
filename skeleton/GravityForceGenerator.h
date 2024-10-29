#pragma once

#include "ForceGenerator.h"
#include "Vector3D.h"

class GravityForceGenerator : public ForceGenerator
{
public:
    GravityForceGenerator(std::list<Particle*>& globalList, Vector3D<> gravityaceleration);
    ~GravityForceGenerator();

    void ApplyForceToParticles(double t) override;

private:
    Vector3D<> gravityAceleration;
};

