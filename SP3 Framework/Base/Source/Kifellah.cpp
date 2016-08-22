#include "Kifellah.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "GameManager.h"
#include "AudioManager.h"

Kifellah::Kifellah(const string& sceneName) : Hero("Kifellah", sceneName)
{

	maxSpeed = 5;
	damage = 10;
	maxHealth = 100;
	health = maxHealth;
	fireRate = 3.0;

	collisionRadius = 1.0f;
	
	tileCollider.SetDetectionHeight(2.0f);
	tileCollider.SetLengthHeight(1.9f);
	tileCollider.SetDetectionWidth(1.0f);
	tileCollider.SetLengthWidth(0.9f);
	tileCollider.SetNumHotspotsHeight(4);
	tileCollider.SetNumHotspotsWidth(4);

}

Kifellah::~Kifellah() 
{
}

void Kifellah::Update(const double& deltaTime) 
{
	if (health > maxHealth) {
		health = maxHealth;
	}

	Hero::Update(deltaTime);

	//Update AnimationFSM
	animationFSM.SetIsMoving(isMoving);
	animationFSM.SetIsShooting(isShooting);
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
		if (currentDirection == MOVE_DIRECTION::RIGHT) {
			SpriteAnimation* sprite = &animationFSM.GetMesh();
			sprite->SetTextureScale(1, 1);
			sprite->SetTextureOffset(0, 0);
		} else if (currentDirection == MOVE_DIRECTION::LEFT) {
			//To flip the texture, we need to scale it then translate.
			SpriteAnimation* sprite = &animationFSM.GetMesh();
			sprite->SetTextureScale(-1, 1);
			if (sprite->column != 0) {
				sprite->textureOffset[1] = 0;
				sprite->textureOffset[0] = (static_cast<float>((sprite->currentFrame) % sprite->column) * 2 + 1) / sprite->column;
			}
		}
		RenderHelper::GetInstance().RenderMesh(animationFSM.GetMesh(), animationFSM.GetTexture(), false);
	modelStack.PopMatrix();
}

void Kifellah::RenderUI() {

	Hero::RenderUI();

}

void Kifellah::Shoot() {

	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SHOOT]) {
		isShooting = true;
		if (shootingCooldown <= 0.0) {
			shootingCooldown = 1.0 / fireRate;
			Bullet& bullet = FetchBullet();			
			bullet.isActive = true;
			bullet.damage = 20.0f;
			bullet.radius = 0.15f;
			bullet.tileSystem = tileSystem;
			bullet.targets = enemies;
			bullet.lifetime = 5.0f;
			bullet.position = position;
			if (currentDirection == MOVE_DIRECTION::LEFT) {
				 bullet.position.x -= 1.4f;
				bullet.velocity.Set(-20, 0);
			} else if (currentDirection == MOVE_DIRECTION::RIGHT) {
				bullet.position.x += 1.4f;
				bullet.velocity.Set(20, 0);
			}
			bullet.mesh = MeshBuilder::GetInstance().GenerateQuad("Bullet");
			bullet.texture.textureArray[0] = TextureManager::GetInstance().AddTexture("Bullet Yellow", "Image//Cyborg_Shooter//Bullets//Bullet_Yellow.tga");
			AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Weapons//Gun_Kifellah.flac", false);
		}
	} else {
		isShooting = false;
	}

}