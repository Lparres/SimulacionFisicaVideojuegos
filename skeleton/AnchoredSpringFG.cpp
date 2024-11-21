#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(std::list<Particle*>& globalList, double k, double resting_length, const Vector3D<>& anchor_pos) :
	SpringForceGenerator(k, resting_length, nullptr)
{
	_other = new Particle(globalList, anchor_pos, Vector3D<>(0, 0, 0), 1, physx::PxGeometryType::Enum::eBOX, 2, physx::PxVec4(0.0, 0.0, 0.0, 1.0));
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete _other;
}
