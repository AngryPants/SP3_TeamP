#include "Turret.h"
#include "Bullet.h"
#include "AudioManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

//Constructor(s) & Destructor
Turret::Turret(const string& sceneName) : Enemy("Turret", sceneName) {

	//Health
	maxHealth = 100.0f;
	currentHealth = maxHealth;

	//Movement
	maxSpeed = 0.0f;

	//Combat
	damage = 10.0f;
	fireRate = 0.5;
	collisionRadius = 1.0f;

	//Line Of Sight
	viewAngle = 15.0f;
	viewRange = 10.0f;

	//Alerting
	alertTime = 5.0f;
	alertRadius = 10.0f;

	//Collider
	tileCollider.SetDetectionHeight(2.0f);
	tileCollider.SetDetectionWidth(2.0f);
	tileCollider.SetLengthHeight(1.9f);
	tileCollider.SetLengthWidth(1.9f);
	tileCollider.SetNumHotspotsWidth(4);
	tileCollider.SetNumHotspotsHeight(4);

	//Current State
	currentState = STATE::PATROL;

	//Patrol
	patrolTime = 3.0f;

	//Combat
	cannotSeePlayerTimer = 5.0f;

	//Bullet
	bulletMesh = MeshBuilder::GetInstance().GenerateCircle("Turret Bullet", Color(1, 0, 0), 12, 0.5f);

}

Turret::~Turret() {
}

//Combat
void Turret::Attack() {
	
	isAttacking = true;
	if (attackCooldown <= 0.0) {
		attackCooldown = 1.0 / fireRate;
		Bullet& bullet = FetchBullet();
		//cout << "Fetching Bullet" << endl;
		bullet.isActive = true;
		bullet.damage = damage;
		bullet.radius = 0.1f;
		bullet.lifetime = 5.0f;
		bullet.position = position;
		bullet.position.y += 0.5f;
		bullet.velocity = GetForwardDirection() * 5.0f;
		//AudioManager::GetInstance().PlayAudio2D("Turret_Shot.flac", false);
	}

}

//Movement
void Turret::Fall(const double& deltaTime) {

	//Turret can only fall.
	Vector2 acceleration(0, gravity);
	velocity += acceleration * deltaTime;

	position += velocity * deltaTime;

	vector<unsigned int>collisionResult = CheckCollisionDown();
	onGround = false;
	for (unsigned int i = 0; i < collisionResult.size(); ++i) {
		unsigned int terrain = GetTileInfo(TILE_INFO::TERRAIN, collisionResult[i]);
		if (terrain != 0) {
			int tileRow = tileSystem->GetTile(position.y - tileCollider.GetDetectionHeight() * 0.5f);
			position.y = (static_cast<float>(tileRow) + 0.5f) * tileSystem->GetTileSize() + tileCollider.GetDetectionHeight() * 0.5f;
			velocity.y = 0;
			onGround = true;
			break;
		}
	}

}

//Virtual Function(s)
void Turret::Update(const double& deltaTime) {

	Character::Update(deltaTime);	
	isAttacking = false;

	if (currentHealth <= 0.0f) {
		currentState = STATE::DEAD;
	}

	switch (currentState) {
		case STATE::PATROL: {
			Patrol(deltaTime);
		}
		break;
		case STATE::COMBAT: {
			Combat(deltaTime);
		}
		break;
		case STATE::DEAD: {
			Dead(deltaTime);
		}
		break;
	}

	Fall(deltaTime);
	UpdateBullets(deltaTime);
	animationFSM.SetIsShooting(isAttacking);
	animationFSM.SetIsDead(isDead);
	animationFSM.Update(deltaTime);

}

void Turret::Render() {

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

	RenderBullets();

}

void Turret::RenderUI() {
}

void Turret::RenderBullets() {

	//Mesh* bulletMesh = MeshBuilder::GetInstance().GenerateSphere("Turret Bullet", Color(1, 0, 0), 12, 12);
	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	for (vector<Bullet*>::iterator bulletIter = bullets.begin(); bulletIter != bullets.end(); ++bulletIter) {
		Bullet* bulletPtr = *bulletIter;
		if (bulletPtr->isActive) {
			modelStack.PushMatrix();
				modelStack.Translate(bulletPtr->position.x, bulletPtr->position.y, 0);
				modelStack.Rotate(Math::RadianToDegree(atan2(bulletPtr->velocity.y, bulletPtr->velocity.x)), 0, 0, 1);
				modelStack.Scale(bulletPtr->radius * 2.0f, bulletPtr->radius * 2.0f, 1.0f);
				RenderHelper::GetInstance().RenderMesh(*bulletMesh);
			modelStack.PopMatrix();
		}
	}

}

//States
void Turret::Patrol(const double& deltaTime) {

	patrolTime -= static_cast<float>(deltaTime);
	if (patrolTime < 0.0f) {
		patrolTime = Math::RandFloatMinMax(1.0, 5.0);
		if (Math::RandInt() % 2 == 0) {
			FaceLeft();
		} else {
			FaceRight();
		}
	}

	if (CanSeePlayer()) {
		isAlerted = true;
		currentState = STATE::COMBAT;
	}

}

void Turret::Combat(const double& deltaTime) {
	
	if (target->position.x < position.x) {
		FaceLeft();
	} else {
		FaceRight();
	}

	if (CanSeePlayer()) {
		cannotSeePlayerTimer = 5.0f;
	} else {
		cannotSeePlayerTimer -= static_cast<float>(deltaTime);
	}

	if (cannotSeePlayerTimer > 0.0f) {
		Attack();
	} else {
		cannotSeePlayerTimer = 5.0f;
		currentState = STATE::PATROL;
		isAlerted = false;
	}

}

void Turret::Dead(const double& deltaTime) {

	if (!isDead) {
		isDead = true;
		if (target != nullptr) {
			target->AddScore(100);
		}
	}

}

void Turret::Reset() {

	Enemy::Reset();

	cannotSeePlayerTimer = 5.0f;
	currentState = STATE::PATROL;
	patrolTime = 3.0f;

}

//Combat
bool Turret::TakeDamage(const int& damage) {

	bool tookDamage = Character::TakeDamage(damage);

	if (tookDamage && target != nullptr) {
		if (target->position.x < position.x) {
			FaceLeft();
			currentState = STATE::COMBAT;
		} else if (target->position.x > position.x) {
			FaceRight();
			currentState = STATE::COMBAT;			
		}
	}

	return tookDamage;

}

void Turret::Alert() {

	Enemy::Alert();
	currentState = STATE::COMBAT;

}