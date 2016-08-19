#include "Physics.h"

Physics::Physics() {
}

Physics::~Physics() {
}

float Physics::GetAccelerationFM(float F, float M) {

	return F/M;

}

float Physics::GetAccelerationVUT(float v, float u, float t) {

	return (v - u)/t;

}


float Physics::GetVelocityUTA(float u, float t, float a) {

	return u + a*t;

}

float Physics::GetVelocityUAS(float u, float a, float s) {

	return sqrt(u*u + 2*a*s);

}

float Physics::GetDisplacementUVT(float u, float v, float t) {

	return 0.5 * (v + u) * t;

}

float Physics::GetDisplacementUTA(float u, float t, float a) {

	return u*t + 0.5*a*t*t;

}

float Physics::GetMomentum(float v, float m) {

	return v * m;

}

float Physics::GetImpulse(float F, float t) {

	return F * t;

}

float Physics::GetDistance(Vector3 a, Vector3 b) {

	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));

}