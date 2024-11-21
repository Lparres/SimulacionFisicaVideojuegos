#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	~SpringForceGenerator();
	virtual void UpdateForce(Particle* particle, double t);

	inline void setK(double k) { _k = k; };

protected:
	double _k;	// Elastic Coefficient
	double _resting_length;
	Particle* _other;
};

