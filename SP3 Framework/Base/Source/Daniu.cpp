#include "Daniu.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "GameManager.h"
#include "AudioManager.h"

Daniu::Daniu(const string& sceneName) : Hero("Daniu", sceneName)
{

	maxSpeed = 4;
	damage = 15;
	maxHealth = 100;
	currentHealth = maxHealth;
	fireRate = 3.0;
	abilityAccumulatedTime = 0.0;

	collisionRadius = 1.0f;

	tileCollider.SetDetectionHeight(2.0f);
	tileCollider.SetLengthHeight(1.9f);
	tileCollider.SetDetectionWidth(1.0f);
	tileCollider.SetLengthWidth(0.9f);
	tileCollider.SetNumHotspotsHeight(4);
	tileCollider.SetNumHotspotsWidth(4);

	//Mesh & Textures
	mesh = MeshBuilder::GetInstance().GenerateQuad("Quad");
	specialAbility.textureArray[0] = TextureManager::GetInstance().AddTexture("abilityDaniu", "Image//Cyborg_Shooter//Characters//Heroes//Daniu_Overlay.tga");
}

Daniu::~Daniu()
{
}

void Daniu::Update(const double& deltaTime)
{
	if (currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}

	Hero::Update(deltaTime);

	//Update AnimationFSM
	animationFSM.SetIsMoving(isMoving);
	animationFSM.SetIsShooting(isAttacking);
	animationFSM.SetOnGround(onGround);
	/*if (currentDirection == MOVE_DIRECTION::RIGHT) {
	animationFSM.SetDirection(AnimationFSM_Daniu::MOVE_DIRECTION::RIGHT);
	} else if (currentDirection == MOVE_DIRECTION::LEFT) {
	animationFSM.SetDirection(AnimationFSM_Daniu::MOVE_DIRECTION::LEFT);
	}*/
	animationFSM.Update(deltaTime);

	//Hero::Respawn();

}

void Daniu::Render()
{
	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, 0);
	modelStack.Scale(4, 4, 1);
	SpriteAnimation* sprite = &animationFSM.GetMesh();
	if (GetForwardDirection().x > 0) {		
		sprite->SetTextureScale(1, 1);
		sprite->SetTextureOffset(0, 0);
	} else {
		//To flip the texture, we need to scale it then translate.
		sprite->SetTextureScale(-1, 1);
		if (sprite->animation->column != 0) {
			sprite->textureOffset[1] = 0;
			sprite->textureOffset[0] = (static_cast<float>((sprite->animation->currentFrame) % sprite->animation->column) * 2 + 1) / sprite->animation->column;
		}
	}
	RenderHelper::GetInstance().RenderMesh(animationFSM.GetMesh(), animationFSM.GetTexture(), false);
	modelStack.PopMatrix();

	RenderBullets();

}

void Daniu::RenderUI() {

	Hero::RenderUI();
	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	if (GetAbilityActive())
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 0);
		modelStack.Scale(100, 100, 1);
		RenderHelper::GetInstance().RenderMesh(*mesh, specialAbility, false);
		modelStack.PopMatrix();
	}
}

void Daniu::RenderBullets() {

	Mesh* bulletMesh = MeshBuilder::GetInstance().GenerateQuad("Daniu Bullet");
	Texture texture;
	texture.textureArray[0] = TextureManager::GetInstance().AddTexture("Bullet Daniu", "Image//Cyborg_Shooter//Bullets//Bullet_Red.tga");
	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	for (vector<Bullet*>::iterator bulletIter = bullets.begin(); bulletIter != bullets.end(); ++bulletIter) {
		Bullet* bulletPtr = *bulletIter;
		if (bulletPtr->isActive) {
			modelStack.PushMatrix();
				modelStack.Translate(bulletPtr->position.x, bulletPtr->position.y, 0);
				modelStack.Rotate(Math::RadianToDegree(atan2(bulletPtr->velocity.y, bulletPtr->velocity.x)), 0, 0, 1);
				modelStack.Scale(0.2f, 0.2f, 1.0f);
				RenderHelper::GetInstance().RenderMesh(*bulletMesh, texture);
			modelStack.PopMatrix();
		}
	}

}

void Daniu::Attack() {

	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SHOOT]) {
		isAttacking = true;
		if (attackCooldown <= 0.0) {
			attackCooldown = 1.0 / fireRate;
			Bullet& bullet = FetchBullet();
			bullet.isActive = true;
			bullet.damage = 20.0f;
			bullet.radius = 0.15f;
			bullet.lifetime = 5.0f;
			bullet.position = position;
			bullet.position.y += 0.4f;
			bullet.position.x += GetForwardDirection().x * 1.6f;
			bullet.velocity = GetForwardDirection() * 20.0f;
			AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Weapons//Gun_Kifellah.flac", false);
		}
	}
	else {
		isAttacking = false;
	}

}

void Daniu::SpecialAbility(const double &deltaTime)
{
	Hero::SpecialAbility(deltaTime);
	if (GetAbilityActive())
		fireRate = 6.0;
	else
		fireRate = 3.0;

	if (GetAbilityActive())
		abilityAccumulatedTime += deltaTime * 10;
	if (abilityAccumulatedTime > 1)
	{
		abilityAccumulatedTime -= 1;
		AddAbilityScore(-1);
	}
	// Deactivates the ability if it was active and the score is above 5
	if (GetAbilityActive() && GetAbilityScore() <= 0)
	{
		SetAbilityActive(false);
	}
}