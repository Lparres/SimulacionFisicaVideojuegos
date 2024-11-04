#pragma once

#include <list>
#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator() {};

	~ForceGenerator() {};

	virtual void UpdateForce(Particle* p, double t) = 0;

};

