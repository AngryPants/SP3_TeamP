/*******************************************************************************/
/*!
\file Camera.cpp
\author Lim Ngian Xin Terry
\par email: lnxterry\@gmail.com

\brief
CPP file for Camera.
*/
/*******************************************************************************/

#include "Camera.h"
#include "Mtx44.h"
#include <iostream>

using std::cout;
using std::endl;

//Constructor(s) & Destructor

Camera::Camera() : EntityBase("Camera") {

	this->position.SetZero();
	this->up.Set(0, 1, 0);
	this->target.Set(0, 0, 1);

	isOrtho = false;
	this->nearClippingPlane = 0.3f;
	this->farClippingPlane = 1000.0f;
	SetFOV(60.0f);
	this->orthoSize = 5.0f;

}

Camera::~Camera() {
}

//FOV

void Camera::SetFOV(const float& FOV) {

	if (FOV < 1.0f) {
		this->FOV = 1.0f;
	} else if (FOV > 179.0f) {
		this->FOV = 179.0f;
	}

	this->FOV = FOV;

}

float Camera::GetFOV() {

	return this->FOV;

}

//Ortho size
void Camera::SetOrthoSize(const float& orthoSize) {

	this->orthoSize = orthoSize;

}

float Camera::GetOrthoSize() const {

	return this->orthoSize;

}

float Camera::GetOrthoWidth() const {

	return static_cast<float>(aspectRatio.x) / static_cast<float>(aspectRatio.y) * orthoSize;

}

//Projection
void Camera::SetOrtho() {

	if (this->isOrtho == false) {
		this->isOrtho = true;
	}

}

void Camera::SetPerspective() {

	if (this->isOrtho == true) {
		this->isOrtho = false;
		if (this->nearClippingPlane < 0.01f) {
			this->nearClippingPlane = 0.01f;
		}
		if (this->farClippingPlane < this->nearClippingPlane) {
			this->farClippingPlane = this->nearClippingPlane + 0.01f;
		}
	}

}

bool Camera::IsOrtho() const {

	return this->isOrtho;

}

//Clipping Planes

void Camera::SetNearClippingPlane(const float& nearClippingPlane) {
	
	if (nearClippingPlane > this->farClippingPlane) {
		this->nearClippingPlane = this->farClippingPlane - 0.01f;
	} else if (nearClippingPlane < 0.01f && isOrtho == false) {
		this->nearClippingPlane = 0.01f;
	} else {
		this->nearClippingPlane = nearClippingPlane;
	}

}

void Camera::SetFarClippingPlane(const float& farClippingPlane) {

	if (farClippingPlane < this->nearClippingPlane) {
		this->farClippingPlane = this->nearClippingPlane + 0.01f;
	} else {
		this->farClippingPlane = farClippingPlane;
	}

}

float Camera::GetNearClippingPlane() const {

	return this->nearClippingPlane;

}

float Camera::GetFarClippingPlane() const {

	return this->farClippingPlane;

}

void Camera::Update(const double& deltaTime) {
}