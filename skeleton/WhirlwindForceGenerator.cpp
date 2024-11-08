#include "WhirlwindForceGenerator.h"

WhirlwindForceGenerator::WhirlwindForceGenerator(float windForce, float airFriction, Vector3D<> pos, float width) :
	WindForceGenerator(windForce, airFriction, pos, width)
{}

void WhirlwindForceGenerator::UpdateForce(Particle* p, double t)
{
	if (PositionOnWind(p->GetPosition())) {
		Vector3D<> pToCentre = (p->GetPosition() - position);
		Vector3D<> perpendicular = Vector3D<>(-pToCentre.z, 0, pToCentre.x);
		Vector3D<> f = perpendicular * windForce * airFriction;
		p->ApplyInstantForce(f * t);
	}
}

bool WhirlwindForceGenerator::PositionOnWind(Vector3D<> pos) const
{
	return  (abs(pos.x - position.x) < width / 2) &&
		(abs(pos.y - position.y) < width / 2) &&
		(abs(pos.z - position.z) < width / 2);
}