#include "Bullet.h"
#include "RenderHelper.h"
#include "GraphicsManager.h"
#include "TextureManager.h"
#include "CollisionSystem.h"
#include "Character.h"
#include "TileIndex.h"

Bullet::Bullet(const string& sceneName) : GameEntity("Bullet", sceneName)
{
	//Stats
	damage = 1;
	lifetime = 1.0;
	radius = 0.1f;

	//What can the bullet hit?
	targets = nullptr;

	//Check for collision with walls etc.
	tileSystem = nullptr;

	//Mesh & Texture
	mesh = nullptr;

}

Bullet::~Bullet()
{
}

void Bullet::Update(const double& deltaTime) {

	if (!isActive) {
		return;
	}

	CheckCollisionWithWall();
	DamageTargets(deltaTime);	

	position += velocity * static_cast<float>(deltaTime);

	lifetime -= static_cast<float>(deltaTime);
	if (lifetime < 0) {
		isActive = false;
	}
	
}

void Bullet::DamageTargets(const double& deltaTime) {

	if (targets == nullptr) {
		return;
	}

	for (vector<Character*>::iterator targetIter = (*targets).begin(); targetIter != (*targets).end(); ++targetIter) {
		Character* target = (*targetIter);
		if (target->isActive) {
			float timeToCollision = CollisionSystem::CircleCircle(position, target->position, radius, target->GetCollisionRadius(), velocity, target->velocity);
			if (timeToCollision > 0.0f && timeToCollision < static_cast<float>(deltaTime)) {
				target->TakeDamage(damage);
				isActive = false;
			}
		}
	}

}

//Despawn the bullet if it hits a wall.
void Bullet::CheckCollisionWithWall() {
	
	if (tileSystem == nullptr) {
		return;
	}

	//Find out what row and column we are current in.
	int currentTileCol = tileSystem->GetTile(position.x);
	int currentTileRow = tileSystem->GetTile(position.y);

	//Are we still within the boundaries of the map? If no, despawn.
	if (currentTileCol < 0 || currentTileCol >= tileSystem->GetNumColumns()) {
		isActive = false;
		return;
	} else if (currentTileRow < 0 || currentTileRow >= tileSystem->GetNumRows()) {
		isActive = false;
		return;
	}

	int terrain = GetTileInfo(TILE_INFO::TERRAIN, tileSystem->TileValue(currentTileRow, currentTileCol));
	if (terrain != 0) {
		isActive = false;
	}

}

void Bullet::Render()
{

	if (mesh == nullptr || !isActive) {
		return;
	}

	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, 0);
		modelStack.Rotate(Math::RadianToDegree(atan2(velocity.y, velocity.x)), 0, 0, 1);
		float renderScale = Math::Max(0.01f, radius * 2.0f);
		modelStack.Scale(renderScale, renderScale, 1);
		RenderHelper::GetInstance().RenderMesh(*mesh, texture, false);
	modelStack.PopMatrix();

}

void Bullet::RenderUI()
{
}