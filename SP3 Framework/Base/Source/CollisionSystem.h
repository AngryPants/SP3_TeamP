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
	CollisionSystem();
	virtual ~CollisionSystem();
public:
	static float CircleCircle(Vector2 circlePos1, Vector2 circlePos2, float circleScale1, float circleScale2, float circleVel1, float circleVel2);
	static float LineCircle();
	static float CircleSquare();
};

#endif