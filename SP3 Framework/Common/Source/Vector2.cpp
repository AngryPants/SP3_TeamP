#include "Vector2.h"
#include <cmath>
#include "MyMath.h"

Vector2::Vector2(float x, float y) {

	this->x = x;
	this->y = y;

}

Vector2::Vector2(const Vector2 &rhs) {

	this->x = rhs.x;
	this->y = rhs.y;

}

Vector2::~Vector2() {
}

void Vector2::Set(float x, float y) {

	this->x = x;
	this->y = y;

}

Vector2 Vector2::operator+( const Vector2& rhs ) const {
	
	return Vector2(this->x + rhs.x, this->y + rhs.y);

}

Vector2& Vector2::operator+=(const Vector2& rhs) {

	this->x += rhs.x;
	this->y += rhs.y;

	return *this;

}

Vector2 Vector2::operator-( const Vector2& rhs ) const {
	
	return Vector2(this->x - rhs.x, this->y - rhs.y);

}

Vector2& Vector2::operator-=(const Vector2& rhs) {

	this->x -= rhs.x;
	this->y -= rhs.y;

	return *this;

}

Vector2 Vector2::operator-(void) const {

	return Vector2(-this->x, -this->y);

}

Vector2 Vector2::operator*(const float& scalar) const {

	return Vector2(this->x * scalar, this->y * scalar);

}

Vector2& Vector2::operator*=(const float& scalar) {

	this->x *= scalar;
	this->y *= scalar;

	return *this;

}

float Vector2::Dot( const Vector2& rhs ) const {

	return this->x * rhs.x + this->y * rhs.y;

}

Vector2 Vector2::Normalized(void) {

	float length = this->Length();

	if (length < Math::EPSILON) {
		throw DivideByZero();
	}

	return Vector2(this->x / length, this->y / length);

}

Vector2& Vector2::Normalize() {

	float length = this->Length();

	if (length < Math::EPSILON) {
		throw DivideByZero();
	}

	this->x /= length;
	this->y /= length;

	return *this;

}

//Virtual Function(s)
float Vector2::Length(void) const {

	return sqrt(LengthSquared());

}

void Vector2::SetZero() {

	this->x = 0.0f;
	this->y = 0.0f;

}

float Vector2::LengthSquared() const {

	return (this->x * this->x + this->y * this->y);

}

bool Vector2::IsZero() const {

	return IsEqual(x, 0.0f) && IsEqual(y, 0.0f);

}