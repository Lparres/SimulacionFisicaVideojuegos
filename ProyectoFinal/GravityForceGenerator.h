#pragma once

#include "ForceGenerator.h"
#include "Vector3D.h"

class GravityForceGenerator : public ForceGenerator
{
public:
    GravityForceGenerator(Vector3D<> gravityaceleration);
    ~GravityForceGenerator();

    void UpdateForce(Particle* p, double t) override;

private:
    Vector3D<> gravityAceleration;
};

