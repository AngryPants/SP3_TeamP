#include "Sawblade.h"

#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "TextureManager.h"
#include "RenderHelper.h"
#include "CollisionSystem.h"
#include "Character.h"

Sawblade::Sawblade()
{
	name = "Sawblade";
	initialized = false;
	nodeIter = nodes.begin();
	speed = 10.f;
	damage = 10.f;
	radius = 1.f;
	velocity.Set(0, 0);

	mesh = MeshBuilder::GetInstance().GenerateQuad("Sawblade", Color(1, 1, 1), 1.f);
	texture.textureArray[0] = TextureManager::GetInstance().AddTexture("Sawblade", "Image//Cyborg_Shooter//Others//Saw.tga");
}

void Sawblade::AddNode(unsigned int index, Vector2 position)
{
	nodes.insert(std::pair<unsigned int, Vector2>(index, position));
}

void Sawblade::SawbladeHeroChecker(float deltaTime)
{
	float timeToCollision = CollisionSystem::CircleCircle(position, hero->position, radius, hero->radius, velocity, hero->velocity);
	if (timeToCollision < deltaTime)
		hero->TakeDamage(damage);
}

void Sawblade::Update(const double &deltaTime)
{
	if (!initialized)
	{
		position = nodes.begin()->second;
		nodeIter = nodes.begin();
		initialized = true;
		speed = 10.f;
	}
	if (nodes.size() == 0) {
		std::cout << "Error: Sawblade has no nodes." << std::endl;
		return;
	}
	if (nodeIter == nodes.end()) {
		nodeIter = nodes.begin();
	}

	Vector2 direction = nodeIter->second - position;
	if (direction.LengthSquared() < Math::EPSILON) {
		++nodeIter;
		return;
	}

	velocity += direction.Normalize() * speed * deltaTime;
	position += velocity;

	if (direction.x < 0) {
		if (position.x < nodeIter->second.x) {
			position.x = nodeIter->second.x;
		}
	}
	else {
		if (position.x > nodeIter->second.x) {
			position.x = nodeIter->second.x;
		}
	}

	if (direction.y < 0) {
		if (position.y < nodeIter->second.y) {
			position.y = nodeIter->second.y;
		}
	}
	else {
		if (position.y > nodeIter->second.y) {
			position.y = nodeIter->second.y;
		}
	}

	SawbladeHeroChecker(deltaTime);
	
}

void Sawblade::Render()
{
	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, 0);
		modelStack.Scale(radius, radius, 1);
		RenderHelper::GetInstance().RenderMesh(*mesh, texture, false);
	modelStack.PopMatrix();
}