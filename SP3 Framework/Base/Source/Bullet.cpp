#include "Bullet.h"
#include "RenderHelper.h"
#include "GraphicsManager.h"
#include "TextureManager.h"
#include "CollisionSystem.h"
#include "Character.h"
#include "TileIndex.h"

Bullet::Bullet() {
	//Is this bullet active?
	isActive = false;

	//Stats
	damage = 1;
	lifetime = 1.0;
	radius = 0.1f;

}

Bullet::~Bullet()
{
}

void Bullet::Update(const double& deltaTime) {

	if (!isActive) {
		return;
	}	

	position += velocity * static_cast<float>(deltaTime);

	lifetime -= static_cast<float>(deltaTime);
	if (lifetime < 0) {
		isActive = false;
	}
	
}