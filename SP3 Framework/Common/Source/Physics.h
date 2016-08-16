#ifndef _PHYSICS_H
#define _PHYSICS_H
/****************************************************************************/
/*!
\file Physics.h
\author
\par email:
\brief

*/
/****************************************************************************/
#include <math.h>
#include "Vector3.h"
/******************************************************************************/
/*!
		Class Physics:
\brief
*/
/******************************************************************************/
struct Physics {

public:
	//Constructors & Destructor
	Physics();
	~Physics();

	//Getters
	static float GetAccelerationFM(float F, float M);
	static float GetAccelerationVUT(float v, float u, float t);
	static float GetVelocityUTA(float u, float t, float a);
	static float GetVelocityUAS(float u, float a, float s);
	static float GetDisplacementUVT(float u, float v, float t);
	static float GetDisplacementUTA(float u, float t, float a);
	static float GetMomentum(float v, float m);
	static float GetImpulse(float F, float t);
	static float GetDistance(Vector3 a, Vector3 b);

};

#endif