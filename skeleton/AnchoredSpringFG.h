#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringFG : public SpringForceGenerator
{
public:
	AnchoredSpringFG(std::list<Particle*>& globalList, double k, double resting_length, const Vector3D<>& anchor_pos);
	~AnchoredSpringFG();
};

