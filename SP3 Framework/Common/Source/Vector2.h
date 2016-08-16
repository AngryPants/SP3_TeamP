#ifndef VECTOR2_H
#define VECTOR2_H

#include "Vector.h"

struct Vector2 : public Vector {

	float x, y;
	Vector2(float x = 0.0f, float y = 0.0f); //default constructor
	Vector2(const Vector2 &rhs); //copy constructor
	virtual ~Vector2();
	void Set(float x, float y); //Set all data
	Vector2 operator+(const Vector2& rhs) const; //Vector addition
	Vector2& operator+=(const Vector2& rhs); //Vector addition
	Vector2 operator-(const Vector2& rhs) const; //Vector subtraction
	Vector2& operator-=(const Vector2& rhs); //Vector subtraction
	Vector2 operator-(void) const; //Unary negation
	Vector2 operator*(const float& scalar) const; //Scalar multiplication
	Vector2& operator*=(const float& scalar); //Scalar multiplication
	float Dot(const Vector2& rhs) const; //Dot product
	Vector2 Normalized(void); //Return a copy of this vector, normalized
	Vector2& Normalize();

	//Virtual Function(s)
	virtual bool IsZero() const; //Check if data is 0.
	virtual float Length() const; //Get Magnitude
	virtual float LengthSquared() const; //Get Square of Magnitude

};

#endif