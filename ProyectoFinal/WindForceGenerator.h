#pragma once

#include "ForceGenerator.h"
#include "Vector3D.h"

class WindForceGenerator : public ForceGenerator
{
public:
    WindForceGenerator(Vector3D<> windDirection, float windForce, float airFriction, Vector3D<> pos, float width);
    WindForceGenerator(float windForce, float airFriction, Vector3D<> pos, float width);
    ~WindForceGenerator();

    void UpdateForce(Particle* p, double t) override;

    bool PositionOnWind(Vector3D<> pos) const;

protected:
    Vector3D<> windVelocity;
    Vector3D<> position;
    float windForce;
    float airFriction;
    float width;

};

