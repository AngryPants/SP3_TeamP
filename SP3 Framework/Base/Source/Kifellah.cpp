#include "Kifellah.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

Kifellah::Kifellah() {
	
	name = "Kifellah";
	speed = 15;
	damage = 10;
	health = 100;
	fireRate = 3.0;

	onGround = true;

	animations[IDLE].Set(0, 9, true, 1.0, true);
	animations[RUN].Set(10, 19, true, 1.0, true);
	animations[JUMP].Set(20, 29, false, 0.5, true);
	animations[SHOOT].Set(30, 34, true, 1 / fireRate, true);
	animations[RUN_SHOOT].Set(40, 49, true, 1.0, true);
	animations[DEAD].Set(50, 59, false, 1.0, true);
	mesh = MeshBuilder::GetInstance().GenerateSpriteAnimation("Kifellah", 6, 10);
	mesh->animation = &animations[IDLE];
	texture.textureArray[0] = TextureManager::GetInstance().AddTexture("Kifellah", "Image//Cyborg_Shooter//Characters//Heroes//Hero_Kifellah.tga");

	//Left	
	hotspots[0].Set(-0.25f, 0.25f);
	hotspots[1].Set(-0.25f, -0.25f);
	//Right
	hotspots[2].Set(0.25f, 0.25f);
	hotspots[3].Set(0.25f, -0.25f);
	//Up
	hotspots[4].Set(-0.25f, 0.25f);
	hotspots[5].Set(0.25f, 0.25f);
	//Down
	hotspots[6].Set(-0.25f, -0.25f);
	hotspots[7].Set(0.25f, -0.25f);

}

Kifellah::~Kifellah() {
}

void Kifellah::Update(const double& deltaTime) 
{
	float textureScaleU = 0.0f;
	float textureScaleV = 0.0f;
	mesh->GetTextureScale(textureScaleU, textureScaleV);

	Vector2 acceleration;
	bool shouldIdle = true;
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_RIGHT]) 
	{
		shouldIdle = false;
		if (textureScaleU != 1.0f) 
		{
			mesh->SetTextureScale(1.0f, 1.0f);
		}
		mesh->animation = &animations[RUN];
		acceleration.x += InputManager::GetInstance().GetInputInfo().keyValue[INPUT_MOVE_RIGHT] * deltaTime * 50.0f;
	} 
	else if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_LEFT]) 
	{
		shouldIdle = false;
		if (textureScaleU != -1.0f) 
		{
			mesh->SetTextureScale(-1.0f, 1.0f);
		}
		mesh->animation = &animations[RUN];
		acceleration.x -= InputManager::GetInstance().GetInputInfo().keyValue[INPUT_MOVE_LEFT] * deltaTime * 50.0f;
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_JUMP])
	{
		shouldIdle = false;
		if (textureScaleU != 1.0f)
		{
			mesh->SetTextureScale(1.0f, 1.0f);
		}
		mesh->animation = &animations[SHOOT];
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_RIGHT] && InputManager::GetInstance().GetInputInfo().keyDown[INPUT_JUMP])
	{
		shouldIdle = false;
		if (textureScaleU != 1.0f)
		{
			mesh->SetTextureScale(1.0f, 1.0f);
		}
		mesh->animation = &animations[RUN_SHOOT];
		acceleration.x += InputManager::GetInstance().GetInputInfo().keyValue[INPUT_MOVE_RIGHT] * deltaTime * 50.0f;
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_LEFT] && InputManager::GetInstance().GetInputInfo().keyDown[INPUT_JUMP])
	{
		shouldIdle = false;
		if (textureScaleU != -1.0f)
		{
			mesh->SetTextureScale(-1.0f, 1.0f);
		}
		mesh->animation = &animations[RUN_SHOOT];
		acceleration.x -= InputManager::GetInstance().GetInputInfo().keyValue[INPUT_MOVE_LEFT] * deltaTime * 50.0f;
	}

	if (shouldIdle) 
	{
		mesh->animation = &animations[IDLE];
	}

	position += acceleration * deltaTime * 20.0f;

	mesh->Update(deltaTime);
}

void Kifellah::Render() 
{
	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, 0);
		RenderHelper::GetInstance().RenderMesh(*mesh, texture, false);
	modelStack.PopMatrix();
}

void Kifellah::RenderUI() {

}