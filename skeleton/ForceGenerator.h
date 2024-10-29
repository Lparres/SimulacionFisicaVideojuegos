#pragma once

#include <list>
#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator(std::list<Particle*>& globalList) :
	globalListRef(globalList)
	{};

	~ForceGenerator() {};

	virtual void ApplyForceToParticles(double t) = 0;

protected:
	std::list<Particle*>& globalListRef;
};

