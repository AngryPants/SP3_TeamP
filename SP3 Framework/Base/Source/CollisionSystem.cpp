#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{

}

CollisionSystem::~CollisionSystem()
{
}

float CollisionSystem::CircleCircle(Vector2 circlePos1, Vector2 circlePos2, float circleScale1, float circleScale2, float circleVel1, float circleVel2)
{
	Vector2 rel = circleVel1 - circleVel2;
	Vector2 dir = circlePos1 - circlePos2;
	float r = circleScale1 + circleScale2;
	float dot = rel.Dot(dir);

	if (dot > 0)
		return -1;

	float a = rel.LengthSquared();
	float b = 2 * rel.Dot(dir);
	float c = dir.LengthSquared() - r * r;
	float d = b * b - 4 * a * c;

	float t = (-b - sqrt(d)) / (2 * a);
	if (t < 0)
		t = (-b + sqrt(d)) / (2 * a);
	return t;
}

float CollisionSystem::LineCircle(Vector2 circlePos1, Vector2 circlePos2, float circleScale2, float circleVel1, float circleVel2)
{
	return CircleCircle(circlePos1, circlePos2, 0, circleScale2, circleVel1, circleVel2);
}