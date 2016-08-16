#include "Camera2D.h"
#include "TileMap.h"
#include "Character.h"

using namespace std;

Camera2D::Camera2D() {

	target.SetZero();
	position.Set(0, 0, 1);
	up.Set(0, 1, 0);
	SetOrtho();
	SetOrthoSize(9);
	aspectRatio.Set(1024, 800);
	followTarget = nullptr;
	tileMap = nullptr;
	deadZoneX = 0.25;
	deadZoneY = 0.25;

}

Camera2D::~Camera2D() {
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

}