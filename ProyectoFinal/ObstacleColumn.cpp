#include "ObstacleColumn.h"

using namespace physx;

ObstacleColumn::ObstacleColumn(PxVec3 columnSize, PxTransform transform, PxVec3 obstacleSize, float obstacleMass, PxScene* scene, std::vector<Obstacle*>* obs)
{
	for (int coordY = 0; coordY < columnSize.y; coordY++) {
		for (int coordX = 0; coordX < columnSize.x; coordX++) {
			for (int coordZ = 0; coordZ < columnSize.z; coordZ++) {
				PxTransform obstacleTr = PxTransform(PxVec3(transform.p.x + coordX * obstacleSize.x * 2, transform.p.y + coordY * obstacleSize.y * 2, transform.p.z + coordZ * obstacleSize.z * 2 ));
				obstacles.push_back(new Obstacle(obstacleSize, obstacleTr, obstacleMass, scene));
				obs->push_back(obstacles.back());
			}
		}
	}
}
