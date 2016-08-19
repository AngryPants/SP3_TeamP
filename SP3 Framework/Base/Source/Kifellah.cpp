#include "Kifellah.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

Kifellah::Kifellah() 
{
	
	name = "Kifellah";
	speed = 15;
	damage = 10;
	maxHealth = 100;
	health = maxHealth;
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

	scale.Set(4, 4);
	tileCollider.SetDetectionHeight(scale.y * 0.5f);
	tileCollider.SetDetectionWidth(scale.x * 0.5f);
	tileCollider.SetLengthHeight(scale.y * 0.45f);
	tileCollider.SetLengthWidth(scale.x * 0.45f);
	tileCollider.SetNumHotspotsHeight(4);
	tileCollider.SetNumHotspotsWidth(4);

	//scale.Set(4, 4);
	//tileCollider.SetDetectionHeight(scale.y * 0.5f);
	//tileCollider.SetDetectionWidth(scale.x * 0.5f);
	//tileCollider.SetLengthHeight(scale.y * 0.45f);
	//tileCollider.SetLengthWidth(scale.x * 0.45f);
	//tileCollider.SetNumHotspotsHeight(8);
	//tileCollider.SetNumHotspotsWidth(8);

}

Kifellah::~Kifellah() 
{
}

void Kifellah::Update(const double& deltaTime) 
{
	float textureScaleU = 0.0f;
	float textureScaleV = 0.0f;
	mesh->GetTextureScale(textureScaleU, textureScaleV);

	bool shouldIdle = true;
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_RIGHT]) 
	{
		shouldIdle = false;
		if (textureScaleU != 1.0f) 
		{
			mesh->SetTextureScale(1.0f, 1.0f);
		}
		mesh->animation = &animations[RUN];
	}
	else if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_JUMP] && InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_RIGHT])
	{
		shouldIdle = false;
		if (textureScaleU != 1.0f)
		{
			mesh->SetTextureScale(1.0f, 1.0f);
		}
		mesh->animation = &animations[JUMP];
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_LEFT]) 
	{
		shouldIdle = false;
		if (textureScaleU != -1.0f) 
		{
			mesh->SetTextureScale(-1.0f, 1.0f);
		}
		mesh->animation = &animations[RUN];
	}	
	else if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_JUMP] && InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_LEFT])
	{
		shouldIdle = false;
		if (textureScaleU != -1.0f)
		{
			mesh->SetTextureScale(-1.0f, 1.0f);
		}
		mesh->animation = &animations[JUMP];
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SHOOT])
	{
		shouldIdle = false;
		if (textureScaleU != 1.0f)
		{
			mesh->SetTextureScale(1.0f, 1.0f);
		}
		mesh->animation = &animations[SHOOT];
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_RIGHT] && InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SHOOT])
	{
		shouldIdle = false;
		if (textureScaleU != 1.0f)
		{
			mesh->SetTextureScale(1.0f, 1.0f);
		}
		mesh->animation = &animations[RUN_SHOOT];
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_LEFT] && InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SHOOT])
	{
		shouldIdle = false;
		if (textureScaleU != -1.0f)
		{
			mesh->SetTextureScale(-1.0f, 1.0f);
		}
		mesh->animation = &animations[RUN_SHOOT];
	}

	if (shouldIdle) 
	{
		mesh->animation = &animations[IDLE];
	}

	if (health > maxHealth)
	{
		health = maxHealth;
	}

	Hero::Respawn(maxHealth);
	mesh->Update(deltaTime);
	Hero::Update(deltaTime);
}

void Kifellah::Render() 
{
	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, 0);
		modelStack.Scale(scale.x, scale.y, 1);
		RenderHelper::GetInstance().RenderMesh(*mesh, texture, false);
	modelStack.PopMatrix();
}

void Kifellah::RenderUI() {

}