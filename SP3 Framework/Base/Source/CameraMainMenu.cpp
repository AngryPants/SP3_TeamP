#include "CameraMainMenu.h"
#include "Mtx44.h"

CameraMainMenu::CameraMainMenu(const string& sceneName) : Camera("Camera Main Menu", sceneName) {

	position.SetZero();
	target.Set(0, 0, -1);
	up.Set(0, 1, 0);
	rotation.SetZero();

}

CameraMainMenu::~CameraMainMenu() {
}

void CameraMainMenu::Roll(const float& rotation) {

	this->rotation.z += rotation;

}

void CameraMainMenu::SetRoll(const float& rotation) {

	this->rotation.z = rotation;

}

void CameraMainMenu::Pitch(const float& rotation) {

	this->rotation.x += rotation;

}

void CameraMainMenu::SetPitch(const float& rotation) {

	this->rotation.x = rotation;

}

void CameraMainMenu::Yaw(const float& rotation) {

	this->rotation.y += rotation;

}

void CameraMainMenu::SetYaw(const float& rotation) {

	this->rotation.y = rotation;

}

void CameraMainMenu::CalculateVectors() {

	enum ROTATION_AXIS {
		X,
		Y,
		Z,
		NUM_AXIS,
	};
	Mtx44 rotationMatrix[NUM_AXIS];
	rotationMatrix[X].SetToRotation(rotation.x, 1, 0, 0);
	rotationMatrix[Y].SetToRotation(rotation.y, 0, 1, 0);
	rotationMatrix[Z].SetToRotation(rotation.z, 0, 0, 1);

	Mtx44 viewMatrix;
	viewMatrix.SetToTranslation(0, 0, 1);
	viewMatrix = rotationMatrix[Y] * rotationMatrix[X] * rotationMatrix[Z] * viewMatrix;
	Vector3 view(viewMatrix.a[12], viewMatrix.a[13], viewMatrix.a[14]);
	target = position + view;

	Mtx44 upMatrix;
	upMatrix.SetToTranslation(0, 1, 0);
	upMatrix =  rotationMatrix[Y] * rotationMatrix[X] * rotationMatrix[Z] * upMatrix;
	up.Set(upMatrix.a[12], upMatrix.a[13], upMatrix.a[14]);

}

void CameraMainMenu::Update(const double& deltaTime) {

	CalculateVectors();

}

Vector3 CameraMainMenu::GetRotation() const {

	return this->rotation;

}