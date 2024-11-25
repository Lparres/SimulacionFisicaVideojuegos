#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(Vector3D<> windDirection, float windForce, float airFriction, Vector3D<> pos, float width) :
	ForceGenerator(),
	windVelocity(windDirection.GetNormalized() * windForce),
	windForce(windForce),
	airFriction(airFriction),
	position(pos),
	width(width)
{
	
}

WindForceGenerator::WindForceGenerator(float windForce, float airFriction, Vector3D<> pos, float width) :
	ForceGenerator(),
	windVelocity(Vector3D<>(0, 0, 0)),
	windForce(windForce),
	airFriction(airFriction),
	position(pos),
	width(width)
{
}

WindForceGenerator::~WindForceGenerator()
{

}

void WindForceGenerator::UpdateForce(Particle* p, double t)
{
	if (PositionOnWind(p->GetPosition())) {
		Vector3D<> f = (windVelocity - p->GetVelocity()) * airFriction;
		p->ApplyInstantForce(f * t);
	}
}

bool WindForceGenerator::PositionOnWind(Vector3D<> pos) const
{
	return  (abs(pos.x - position.x) < width / 2) &&
			(abs(pos.y - position.y) < width / 2) &&
			(abs(pos.z - position.z) < width / 2);
}
