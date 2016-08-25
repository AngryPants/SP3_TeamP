/******************************************************************************/
/*!
\file	Vector3.h
\author Wen Sheng Tang
\par	email: tang_wen_sheng\@nyp.edu.sg
\brief
Struct to define a 3D vector
*/
/******************************************************************************/

#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector.h"

#pragma warning(disable: 4290) //for throw(DivideByZero)

/******************************************************************************/
/*!
		Class Vector3:
\brief	Defines a 3D vector and its methods
*/
/******************************************************************************/
struct Vector3 : public Vector {

	float x, y, z;
	
	Vector3(float a = 0.0, float b = 0.0, float c = 0.0);
	Vector3(const Vector3 &rhs);
	virtual ~Vector3();
	
	void Set( float a = 0, float b = 0, float c = 0 ); //Set all data
	virtual void SetZero(void); //Set all data to zero
	virtual bool IsZero(void) const; //Check if data is zero

	Vector3 operator+(const Vector3& rhs) const; //Vector addition
	Vector3& operator+=( const Vector3& rhs ); 
	
	Vector3 operator-(const Vector3& rhs) const; //Vector subtraction
	Vector3& operator-=(const Vector3& rhs);
	
	Vector3 operator-(void) const; //Unary negation
	
	Vector3 operator*(float scalar) const; //Scalar multiplication
	Vector3& operator*=(float scalar);

	bool operator==(const Vector3& rhs) const; //Equality check
	bool operator!= (const Vector3& rhs) const; //Inequality check

	Vector3& operator=(const Vector3& rhs); //Assignment operator

	virtual float Length(void) const; //Get magnitude
	virtual float LengthSquared (void) const; //Get square of magnitude
	
	float Dot(const Vector3& rhs) const; //Dot product
	float AngleBetween(const Vector3& rhs) const; //Find the angle between these 2 vector3 in degrees.
	Vector3 Cross(const Vector3& rhs) const; //Cross product
	Vector3 Projection(const Vector3& rhs) const; //Projeciton

	Vector3 RotateAroundAxis(float theta, const Vector3& axis); //Axis Angle Rotation

	//Return a copy of this vector, normalized
	//Throw a divide by zero exception if normalizing a zero vector
	Vector3 Normalized(void) const throw(DivideByZero);
	
	//Normalize this vector and return a reference to it
	//Throw a divide by zero exception if normalizing a zero vector
	Vector3& Normalize(void) throw(DivideByZero);

	friend std::ostream& operator<<( std::ostream& os, Vector3& rhs); //print to ostream

	friend Vector3 operator*(float scalar, const Vector3& rhs); //what is this for?

};

#endif //VECTOR3_H
