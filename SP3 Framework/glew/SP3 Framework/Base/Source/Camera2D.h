#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "Camera.h"
#include "TileSystem.h"

class Character;

class Camera2D : public Camera {

private:
	Character* followTarget;
	TileSystem* tileSystem;

	float deadZoneX, deadZoneY;

public:
	//Construcor(s) & Destructor
	Camera2D();
	virtual ~Camera2D();

	//Function(s)
	void SetFollowTarget(Character& target); //The target for the camera to follow.
	void RemoveTarget();
	void SetTileSystem(TileSystem& tileMap);
	void RemoveTileSystem();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);

};

#endif