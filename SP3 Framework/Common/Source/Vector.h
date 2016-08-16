#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "MyMath.h"

using Math::DegreeToRadian;
using Math::RadianToDegree;
using Math::EPSILON;

struct Vector {

public:
	//Constructor(s) & Destructor
	Vector();
	virtual ~Vector();

	//Function(s)
	static bool IsEqual(const float& a, const float& b);

	//Virtual Function(s)
	virtual bool IsZero() const = 0; //Check if data is 0.
	virtual float Length() const = 0; //Get Magnitude
	virtual float LengthSquared() const = 0; //Get Square of Magnitude

};

#endif