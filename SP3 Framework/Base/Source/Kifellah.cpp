#include "Kifellah.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "GameManager.h"
#include "AudioManager.h"

Kifellah::Kifellah(const string& sceneName) : Hero("Kifellah", sceneName)
{

	maxSpeed = 7;
	damage = 10;
	maxHealth = 100;
	currentHealth = maxHealth;
	fireRate = 3.0;

	collisionRadius = 1.0f;
	
	tileCollider.SetDetectionHeight(2.0f);
	tileCollider.SetLengthHeight(1.9f);
	tileCollider.SetDetectionWidth(1.0f);
	tileCollider.SetLengthWidth(0.9f);
	tileCollider.SetNumHotspotsHeight(4);
	tileCollider.SetNumHotspotsWidth(4);

	//Mesh & Textures
	mesh = MeshBuilder::GetInstance().GenerateQuad("Quad");
	specialAbility.textureArray[0] = TextureManager::GetInstance().AddTexture("abilityKifellah", "Image//Cyborg_Shooter//Characters//Heroes//Kifellah_Shield.tga");
}

Kifellah::~Kifellah() 
{
}

void Kifellah::Update(const double& deltaTime) 
{
	if (currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}

	Hero::Update(deltaTime);	

	//Update AnimationFSM
	animationFSM.SetIsMoving(isMoving);
	animationFSM.SetIsShooting(isAttacking);
	animationFSM.SetOnGround(onGround);
	animationFSM.Update(deltaTime);

	//Hero::Respawn();
	
}

void Kifellah::Render() 
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
		RenderHelper::GetInstance().RenderMesh(*sprite, animationFSM.GetTexture(), false);
	modelStack.PopMatrix();

	if (GetAbilityActive())
	{	
		modelStack.PushMatrix();
			modelStack.Translate(position.x, position.y, 0);
			modelStack.Scale(4, 4, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, specialAbility, false);
		modelStack.PopMatrix();
	}

	RenderBullets();
}

void Kifellah::RenderUI() {

	Hero::RenderUI();

}

void Kifellah::RenderBullets() {

	Mesh* bulletMesh = MeshBuilder::GetInstance().GenerateQuad("Daniu Bullet");
	Texture texture;
	texture.textureArray[0] = TextureManager::GetInstance().AddTexture("Bullet Kifellah", "Image//Cyborg_Shooter//Bullets//Bullet_Yellow.tga");
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

void Kifellah::Attack() {

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
	} else {
		isAttacking = false;
	}

}

void Kifellah::SpecialAbility(const double &deltaTime)
{
	if (!GetAbilityActive() && GetAbilityAvailable() && (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_ABILITY]))
		AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Kifellah_ShieldActivate.mp3", false);
	Hero::SpecialAbility(deltaTime);
	if (GetAbilityScore() <= 0)
		SetAbilityActive(false);
}

bool Kifellah::TakeDamage(const int &damage)
{
	if (damageCooldown <= 0.0 && !GetAbilityActive())
	{
		this->currentHealth -= damage;
		damageCooldown = 0.5f;
		return true;
	}
	if (damageCooldown <= 0.0 && GetAbilityActive())
	{
		AddAbilityScore(-damage);
		damageCooldown = 0.5f;
		return true;
	}
	return false;
}