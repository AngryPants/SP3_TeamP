#include "Sawblade.h"

#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "TextureManager.h"
#include "RenderHelper.h"
#include "CollisionSystem.h"
#include "Character.h"

Sawblade::Sawblade(const string& sceneName) : GameEntity("Sawblade", sceneName)
{
	name = "Sawblade";
	initialized = false;
	destinationNode = nodes.begin();

	velocity.Set(0, 0);
	speed = 10.f;
	rotation = 0;

	damage = 30;
	radius = 1.5f;

	target = nullptr;

	mesh = MeshBuilder::GetInstance().GenerateQuad("Sawblade", Color(1, 1, 1), 1.f);
	texture.textureArray[0] = TextureManager::GetInstance().AddTexture("Sawblade", "Image//Cyborg_Shooter//Others//Sawblade.tga");
}

void Sawblade::Reset() {

	this->initialized = false;

}

void Sawblade::AddNode(unsigned int index, Vector2 position)
{
	nodes.insert(std::pair<unsigned int, Vector2>(index, position));
}

void Sawblade::DamageTarget(const double& deltaTime)
{
	
	if (target == nullptr)
	{
		cout << "Unable to update sawblade as no hero was attached." << endl;
		return;
	}

	if (target->isActive) {
		float timeToCollision = CollisionSystem::CircleCircle(position, target->position, radius, target->GetCollisionRadius(), velocity, target->velocity);
		if (timeToCollision > 0.0f && timeToCollision < static_cast<float>(deltaTime)) {
			if (target->TakeDamage(damage))
			{
				Vector2 knockback;
				knockback = (target->position - this->position).Normalize() * 25;
				if (knockback.LengthSquared() > Math::EPSILON)
					target->Knockback(knockback);
				else
				{
					target->Knockback(Vector2(-1, 0) * 25);
				}
			}
		}
	}

}

void Sawblade::Update(const double &deltaTime)
{
	
	rotation += static_cast<float>(deltaTime) * 720.0f;
	while (rotation > 360.0f) {
		rotation -= 360.0f;
	}

	MoveToNode(deltaTime);
	DamageTarget(deltaTime);
	
}

void Sawblade::MoveToNode(const double& deltaTime) {

	if (nodes.size() == 0)
	{
		std::cout << "Error: Sawblade has no nodes." << std::endl;
		return;
	}

	if (!initialized)
	{
		//Set ourselves to the first node.
		position = nodes.begin()->second;
		//Our destination node needs to be the second node.
		destinationNode = nodes.begin();
		++destinationNode;
		//Make sure we don't reset ourselves again the next update.
		initialized = true;		
	}
	
	//Make sure our node is valid.
	if (destinationNode == nodes.end()) {
		destinationNode = nodes.begin();
	}

	//Find out what is the direction we should be going.
	Vector2 direction = destinationNode->second - position;

	//Are we already at destination Node?
	if (direction.LengthSquared() < Math::EPSILON) {
		//We're already at the node. No need to move.
		++destinationNode;
		return;
	}

	velocity = direction.Normalized() * speed;
	position += velocity * static_cast<float>(deltaTime);

	if (velocity.x < 0) {
		if (position.x < destinationNode->second.x) {
			position.x = destinationNode->second.x;
		}
	}
	else {
		if (position.x > destinationNode->second.x) {
			position.x = destinationNode->second.x;
		}
	}

	if (velocity.y < 0) {
		if (position.y < destinationNode->second.y) {
			position.y = destinationNode->second.y;
		}
	}
	else {
		if (position.y > destinationNode->second.y) {
			position.y = destinationNode->second.y;
		}
	}

}

void Sawblade::Render()
{
	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, 0);
		modelStack.Rotate(rotation, 0, 0, 1);
		modelStack.Scale(radius * 2.0f, radius * 2.0f, 1);
		RenderHelper::GetInstance().RenderMesh(*mesh, texture, false);
	modelStack.PopMatrix();
}