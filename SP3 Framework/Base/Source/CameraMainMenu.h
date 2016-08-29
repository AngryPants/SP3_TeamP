#ifndef CAMERA_MAIN_MENU_H
#define CAMERA_MAIN_MENU_H

#include "Camera.h"

class CameraMainMenu : public Camera {

private:
	Vector3 rotation;

	void CalculateVectors();

public:
	//Constructor(s) & Destructor
	CameraMainMenu(const string& sceneName);
	virtual ~CameraMainMenu();

	//Function(s)
	virtual void Roll(const float& rotation);
	virtual void Yaw(const float& rotation);
	virtual void Pitch(const float& rotation);
	virtual void SetRoll(const float& rotation);
	virtual void SetYaw(const float& rotation);
	virtual void SetPitch(const float& rotation);

	Vector3 GetRotation() const;

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);

};

#endif