#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Obstacle.h"

class ObstacleColumn
{
public:
	ObstacleColumn(physx::PxVec3 columnSize, physx::PxTransform transform, physx::PxVec3 obstacleSize, float obstacleMass, physx::PxScene* scene, std::vector<Obstacle*>* obs);

private:
	std::vector<Obstacle*> obstacles;
};

