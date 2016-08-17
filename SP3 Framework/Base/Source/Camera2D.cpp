#include "Camera2D.h"
#include "TileMap.h"
#include "Character.h"

using namespace std;

Camera2D::Camera2D() {

	target.Set(0, 0, -1);
	position.SetZero();
	up.Set(0, 1, 0);
	SetOrtho();
	SetOrthoSize(2.5);
	SetFarClippingPlane(100);
	SetNearClippingPlane(-100);
	aspectRatio.Set(1024, 800);
	followTarget = nullptr;
	tileMap = nullptr;
	deadZoneX = 0.25;
	deadZoneY = 0.25;

}

Camera2D::~Camera2D() {
}

void Camera2D::SetFollowTarget(Character& target) {
	
	this->followTarget =  &target;

}

void Camera2D::RemoveTarget() {

	this->followTarget = nullptr;

}

void Camera2D::SetTileMap(TileMap& tileMap) {

	this->tileMap = &tileMap;

}

void Camera2D::RemoveTileMap() {

	this->tileMap = nullptr;

}

void Camera2D::Update(const double& deltaTime) {

	if (followTarget == nullptr) {
		cout << "Unable to update camera as no follow target was set." << endl;
		return;
	} else if (tileMap == nullptr) {
		cout << "Unable to update camera as no tileMap was set." << endl;
		return;
	}

	float maxDistanceToTargetX = deadZoneX * GetOrthoWidth(); //What is the maximum distance we should be following the player.
	float maxDistanceToTargetY = deadZoneY * orthoSize;
	float distanceToTargetX = followTarget->position.x - position.x; //How far are we from the player.
	float distanceToTargetY = followTarget->position.y - position.y;

	if (distanceToTargetX > maxDistanceToTargetX) {	
		position.x = followTarget->position.x - maxDistanceToTargetX;
	} else if (distanceToTargetX < -maxDistanceToTargetX) {
		position.x = followTarget->position.x + maxDistanceToTargetX;
	}

	if (distanceToTargetY > maxDistanceToTargetY) {
		position.y = followTarget->position.y - maxDistanceToTargetY;
	} else if (distanceToTargetY < -maxDistanceToTargetY) {
		position.y = followTarget->position.y + maxDistanceToTargetY;
	}

	//Border of our camera's view
	float rightBorder = position.x + GetOrthoWidth();
	if (rightBorder > tileMap->GetRightBorder()) {
		position.x = tileMap->GetRightBorder() - GetOrthoWidth();
	}
	//Border of our camera's view
	float leftBorder = position.x - GetOrthoWidth();
	if (leftBorder < tileMap->GetLeftBorder()) {
		position.x = tileMap->GetLeftBorder() + GetOrthoWidth();
	}

	//Border of our camera's view
	float topBorder = position.y + orthoSize;
	if (topBorder > tileMap->GetTopBorder()) {
		position.y = tileMap->GetTopBorder() - orthoSize;
	}
	//Border of our camera's view
	float bottomBorder = position.y - orthoSize;
	if (bottomBorder < tileMap->GetBottomBorder()) {
		position.y = tileMap->GetBottomBorder() + orthoSize;
	}
	

}