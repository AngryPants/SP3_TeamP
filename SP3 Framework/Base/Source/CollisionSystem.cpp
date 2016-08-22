#include "CollisionSystem.h"

float CollisionSystem::CircleCircle(Vector2 circlePositionA, Vector2 circlePositionB, float circleRadiusA, float circleRadiusB, Vector2 circleVelocityA, Vector2 circleVelocityB)
{
	Vector2 relativeVelocity = circleVelocityA - circleVelocityB;
	Vector2 relativeDirection = circlePositionA - circlePositionB; //Usually we do B - A but for this case A - B makes calculations easier.
	float combinedRadius = circleRadiusA + circleRadiusB;

	if (relativeVelocity.Dot(relativeDirection) > 0)
		return -1; //We the 2 circles aren't going towards each other.

	float a = relativeVelocity.LengthSquared();
	float b = 2 * relativeVelocity.Dot(relativeDirection);
	float c = relativeDirection.LengthSquared() - combinedRadius * combinedRadius;
	float d = b * b - 4 * a * c;

	float timeToCollision = (-b - sqrt(d)) / (2 * a);
	if (timeToCollision < 0)
		timeToCollision = (-b + sqrt(d)) / (2 * a);
	
	return timeToCollision;

}

float CollisionSystem::LineCircle(Vector2 linePosition, Vector2 circlePosition, float circleRadius, Vector2 lineVelocity, Vector2 circleVelocity)
{
	return CircleCircle(linePosition, circlePosition, 0, circleRadius, lineVelocity, circleVelocity);
}