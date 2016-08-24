#include "Seetwo.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "GameManager.h"
#include "AudioManager.h"

Seetwo::Seetwo(const string& sceneName) : Hero("Seetwo", sceneName)
{

	maxSpeed = 4;
	damage = 10;
	maxHealth = 150;
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
	specialAbility.textureArray[0] = TextureManager::GetInstance().AddTexture("abilitySeetwo", "Image//Cyborg_Shooter//Characters//Heroes//Seetwo_Particle.tga");

	// Particles
	gravity.Set(0.f, 4.9f, 0.f);
	particleCount = 0;
	maxParticles = 100;
}

Seetwo::~Seetwo()
{
}

void Seetwo::Update(const double& deltaTime)
{
	if (currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}

	Hero::Update(deltaTime);
	UpdateParticles(deltaTime);

	//Update AnimationFSM
	animationFSM.SetIsMoving(isMoving);
	animationFSM.SetIsShooting(isShooting);
	animationFSM.SetOnGround(onGround);
	animationFSM.Update(deltaTime);

	//Hero::Respawn();

}

void Seetwo::Render()
{
	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	if (GetAbilityActive())
	{
		RenderParticles();
	}

	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, 0);
	modelStack.Scale(4, 4, 1);
	if (currentDirection == FACING_DIRECTION::RIGHT) {
		SpriteAnimation* sprite = &animationFSM.GetMesh();
		sprite->SetTextureScale(1, 1);
		sprite->SetTextureOffset(0, 0);
	}
	else if (currentDirection == FACING_DIRECTION::LEFT) {
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

void Seetwo::RenderUI() {

	Hero::RenderUI();

}

void Seetwo::Shoot() {

	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SHOOT]) {
		isShooting = true;
		if (shootingCooldown <= 0.0) {
			shootingCooldown = 1.0 / fireRate;
			Bullet& bullet = FetchBullet();
			bullet.isActive = true;
			bullet.damage = 20.0f;
			bullet.radius = 0.3f;
			bullet.tileSystem = tileSystem;
			bullet.targets = enemies;
			bullet.lifetime = 5.0f;
			bullet.position = position;
			bullet.position.y += 0.4f;
			if (currentDirection == FACING_DIRECTION::LEFT) {
				bullet.position.x -= 1.6f;				
				bullet.velocity.Set(-20, 0);
			}
			else if (currentDirection == FACING_DIRECTION::RIGHT) {
				bullet.position.x += 1.6f;
				bullet.velocity.Set(20, 0);
			}
			bullet.mesh = MeshBuilder::GetInstance().GenerateQuad("Bullet");
			bullet.texture.textureArray[0] = TextureManager::GetInstance().AddTexture("Bullet Yellow", "Image//Cyborg_Shooter//Bullets//Bullet_Blue.tga");
			AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Weapons//Gun_Kifellah.flac", false);
		}
	}
	else {
		isShooting = false;
	}

}

void Seetwo::SpecialAbility(const double &deltaTime)
{
	Hero::SpecialAbility(deltaTime);
	static double accumulatedTime = 0;
	if (GetAbilityActive())
		accumulatedTime += deltaTime * 10;
	// Check if ability is available, add ability score over time if both are not true
	if (accumulatedTime > 1 && GetAbilityActive())
	{
		accumulatedTime -= 1;
		currentHealth += maxHealth * 0.5 * 0.02;
		AddAbilityScore(-1);
		//cout << currentHealth << endl;
	}
	// Deactivates the ability if it was active and the score is above 5
	if (GetAbilityActive() && GetAbilityScore() <= 0)
	{
		SetAbilityActive(false);
	}
}

void Seetwo::UpdateParticles(double dt)
{
	if (particleCount < maxParticles)
	{
		ParticleObject *particle = GetParticle();
		particle->type = ParticleObject_TYPE::P_ABILITY_SEETWO;
		particle->scale.Set(0.25, 0.25, 1);
		particle->vel.Set(0.1, 0.1, 0);
		particle->rotationSpeed = Math::RandFloatMinMax(-20.0f, 20.0f);
		particle->pos.Set(position.x + Math::RandFloatMinMax(-1.5f, 1.35f), position.y + Math::RandFloatMinMax(-1.5f, 1.5f), 0);
	}

	for (std::vector<ParticleObject*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		ParticleObject *particle = (ParticleObject *)*it;
		if (particle->active)
		{
			if (particle->type == ParticleObject_TYPE::P_ABILITY_SEETWO)
			{
				particle->vel += gravity * (float)dt;
				particle->pos += particle->vel * (float)dt * 10.f;
			}
			if (particle->pos.y < (position.y - 1.35) || particle->pos.y > (position.y + 1.25))
			{
				particle->active = false;
				particleCount -= 1;
			}
		}
	}
}

ParticleObject *Seetwo::GetParticle(void)
{
	for (std::vector<ParticleObject*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		ParticleObject *particle = (ParticleObject *)*it;
		if (!particle->active)
		{
			particle->active = true;
			particleCount += 1;
			return particle;
		}
	}

	for (unsigned int i = 0; i <= 10; ++i)
	{
		ParticleObject *particle = new ParticleObject(ParticleObject_TYPE::P_ABILITY_SEETWO);
		particleList.push_back(particle);
	}

	ParticleObject *particle = particleList.back();
	particle->active = true;
	particleCount += 1;
	return particle;
}

void Seetwo::RenderParticles()
{
	MS& modelStack = GraphicsManager::GetInstance().modelStack;

	for (std::vector<ParticleObject*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		ParticleObject *particle = (ParticleObject *)*it;
		if (particle->active)
		{
			modelStack.PushMatrix();
			modelStack.Translate(particle->pos.x, particle->pos.y, particle->pos.z);
			modelStack.Rotate(particle->rotation, 0, 0, 1);
			modelStack.Scale(particle->scale.x, particle->scale.y, particle->scale.z);
			RenderHelper::GetInstance().RenderMesh(*mesh, specialAbility, false);
			modelStack.PopMatrix();
		}
	}
}