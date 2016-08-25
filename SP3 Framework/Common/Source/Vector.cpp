#include "Vector.h"

Vector::Vector() {
}

Vector::~Vector() {
}

bool Vector::IsEqual(const float& a, const float& b) {

	return a - b <= Math::EPSILON && b - a <= Math::EPSILON;

}

bool Vector::IsUnitVector() const {

	return IsEqual(LengthSquared(), 1.0f);

}