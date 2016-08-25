#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "MyMath.h"
#include "EntityBase.h"

struct AspectRatio {

public:
	//Variable(s)
	unsigned int x, y;

	//Constructor(s) & Destructor
	AspectRatio(const unsigned int& x = 16, const unsigned int& y = 9) {
		Set(x, y);
	}
	~AspectRatio() {}

	//Setter(s)
	void Set(const unsigned int& x, const unsigned int& y) {
		if (x < 1) {
			this->x = 1;
		} else {
			this->x = x;
		}
		if (y < 1) {
			this->y = 1;
		} else {
			this->y = y;
		}
		unsigned int hcf = Math::HCF(this->x, this->y);
		this->x /= hcf;
		this->y /= hcf;
	}

	float GetRatio() const {
		return static_cast<float>(x) / static_cast<float>(y);
	}

};

class Camera : public EntityBase {

protected:
	//Perspective
	float FOV;
	float nearClippingPlane;
	float farClippingPlane;

	//Orthographic
	bool isOrtho;

	Vector3 position;
	Vector3 target;
	Vector3 up;

public:
	float orthoSize;

	AspectRatio aspectRatio;

	//Constructor(s) & Destructor
	Camera(const string& name, const string& sceneName);
	virtual ~Camera();

	void SetFOV(const float& FOV);
	float GetFOV();

	void SetOrthoSize(const float& orthoSize);
	float GetOrthoSize() const;
	float GetOrthoWidth() const;

	void SetOrtho();
	void SetPerspective();
	bool IsOrtho() const;

	void SetNearClippingPlane(const float& nearClippingPlane);
	void SetFarClippingPlane(const float& nearClippingPlane);
	float GetNearClippingPlane() const;
	float GetFarClippingPlane() const;
	
	virtual void SetPosition(const Vector3& position) {
		this->position = position;
	}
	virtual void SetTarget(const Vector3& target) {
		this->target = target;
	}
	virtual void SetUp(const Vector3& up) {
		this->up = up;
	}

	const Vector3& GetPosition() const {
		return this->position;
	}
	const Vector3& GetTarget() const {
		return this->target;
	}
	const Vector3& GetUp() const {
		return this->up;
	}

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);

};

#endif