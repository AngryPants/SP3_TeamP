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
	destinationNode = nodes.begin();

	velocity.Set(0, 0);
	speed = 10.f;
	rotation = 0;

	damage = 10;
	radius = 5.0f;

	mesh = MeshBuilder::GetInstance().GenerateQuad("Sawblade", Color(1, 1, 1), 1.f);
	texture.textureArray[0] = TextureManager::GetInstance().AddTexture("Sawblade", "Image//Cyborg_Shooter//Others//Saw.tga");

	hero = nullptr;
}

void Sawblade::AddNode(unsigned int index, Vector2 position)
{
	nodes.insert(std::pair<unsigned int, Vector2>(index, position));
}

void Sawblade::DamageHero(const double& deltaTime)
{
	if (hero == nullptr) {
		cout << "Unable to update sawblade as no hero was attached." << endl;
		return;
	}

	float timeToCollision = CollisionSystem::CircleCircle(position, hero->position, radius, hero->radius, velocity, hero->velocity);
	if (timeToCollision < deltaTime)
		hero->TakeDamage(damage);
}

void Sawblade::Update(const double &deltaTime)
{
	
	rotation += deltaTime * 720.0f;
	while (rotation > 360.0f) {
		rotation -= 360.0f;
	}

	MoveToNode(deltaTime);
	DamageHero(deltaTime);
	
}

void Sawblade::MoveToNode(const double& deltaTime) {

	if (nodes.size() == 0)
	{
		std::cout << "Error: Sawblade has no nodes." << std::endl;
		return;
	}

	if (!initialized)
	{
		position = nodes.begin()->second;
		destinationNode = nodes.begin();
		++destinationNode;
		speed = 10.f;
		initialized = true;		
	}
	
	if (destinationNode == nodes.end()) {
		destinationNode = nodes.begin();
	}

	//We're already at the node.
	Vector2 direction = destinationNode->second - position;
	if (direction.LengthSquared() < Math::EPSILON) {
		++destinationNode;
		return;
	}

	velocity = direction.Normalized() * speed;
	position += velocity * deltaTime;

	cout << velocity.x << " " << velocity.y <<endl;

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

void Sawblade::SetHero(Hero& hero) {

	this->hero = &hero;

}

void Sawblade::RemoveHero() {

	this->hero = nullptr;

}

void Sawblade::Render()
{
	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, 0);
		modelStack.Rotate(rotation, 0, 0, 1);
		modelStack.Scale(radius, radius, 1);
		RenderHelper::GetInstance().RenderMesh(*mesh, texture, false);
	modelStack.PopMatrix();
}