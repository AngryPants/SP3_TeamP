#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "Camera.h"

class Character;
class TileMap;

class Camera2D : public Camera {

private:
	Character* followTarget;
	TileMap* tileMap;

	float deadZoneX, deadZoneY;

public:
	//Construcor(s) & Destructor
	Camera2D();
	virtual ~Camera2D();

	//Function(s)
	void SetFollowTarget(Character& target); //The target for the camera to follow.
	void RemoveTarget();
	void SetTileMap(TileMap& tileMap);
	void RemoveTileMap();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);

};

#endif