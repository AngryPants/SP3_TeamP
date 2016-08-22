#pragma once
#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "SingletonTemplate.h"
#include "MyMath.h"
#include "Vector2.h"
#include <vector>

class CollisionSystem : public Singleton<CollisionSystem>
{
	friend class Singleton<CollisionSystem>;

private:
	CollisionSystem() {}
	virtual ~CollisionSystem() {}

public:
	static float CircleCircle(Vector2 circlePositionA, Vector2 circlePositionB, float circleRadiusA, float circleRadiusB, Vector2 circleVelocityA, Vector2 circleVelocityB);
	static float LineCircle(Vector2 linePosition, Vector2 circlePosition, float circleRadius, Vector2 lineVelocity, Vector2 circleVelocity);
};

#endif