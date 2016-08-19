#include "Camera2D.h"
#include "Character.h"
#include "MapRenderer.h"

using namespace std;

Camera2D::Camera2D() {

	target.Set(0, 0, -1);
	position.SetZero();
	up.Set(0, 1, 0);
	SetOrtho();
	SetOrthoSize(8);
	SetFarClippingPlane(100);
	SetNearClippingPlane(-100);
	aspectRatio.Set(1024, 800);
	followTarget = nullptr;
	tileSystem = nullptr;
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

void Camera2D::SetTileSystem(TileSystem& tileSystem) {

	this->tileSystem = &tileSystem;

}

void Camera2D::RemoveTileSystem() {

	this->tileSystem = nullptr;

}

void Camera2D::Update(const double& deltaTime) {

	if (followTarget == nullptr) {
		cout << "Unable to update camera as no follow target was set." << endl;
		return;
	} else if (tileSystem == nullptr) {
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
	float boundaryRight = position.x + GetOrthoWidth();
	if (boundaryRight > tileSystem->GetBoundaryRight()) {
		position.x = tileSystem->GetBoundaryRight() - GetOrthoWidth();
	}
	//Border of our camera's view
	float boundaryLeft = position.x - GetOrthoWidth();
	if (boundaryLeft < tileSystem->GetBoundaryLeft()) {
		position.x = tileSystem->GetBoundaryLeft() + GetOrthoWidth();
	}

	//Border of our camera's view
	float boundaryTop = position.y + orthoSize;
	if (boundaryTop > tileSystem->GetBoundaryTop()) {
		position.y = tileSystem->GetBoundaryTop() - orthoSize;
	}
	//Border of our camera's view
	float boundaryBottom = position.y - orthoSize;
	if (boundaryBottom < tileSystem->GetBoundaryBottom()) {
		position.y = tileSystem->GetBoundaryBottom() + orthoSize;
	}

	target.Set(position.x, position.y, position.z - 1);

	boundaryRight = position.x + GetOrthoWidth();
	boundaryLeft = position.x - GetOrthoWidth();
	boundaryTop = position.y + orthoSize;
	boundaryBottom = position.y - orthoSize;

	MapRenderer::GetInstance().SetStartRow(tileSystem->GetTile(boundaryBottom));
	MapRenderer::GetInstance().SetEndRow(tileSystem->GetTile(boundaryTop) + 1);
	MapRenderer::GetInstance().SetStartColumn(tileSystem->GetTile(boundaryLeft));
	MapRenderer::GetInstance().SetEndColumn(tileSystem->GetTile(boundaryRight) + 1);

}