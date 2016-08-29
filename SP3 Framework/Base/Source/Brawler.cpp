#include "Brawler.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "TextureManager.h"

//Constructor & Destructor
Brawler::Brawler(const string& sceneName) : Enemy("Brawler", sceneName) {

	//State
	currentState = STATE::PATROL;

	//Health
	maxHealth = 100.0f;
	currentHealth = maxHealth;
	canWalkLeft = true;
	canWalkRight = true;

	//Movement
	isMoving = false;
	maxSpeed = Math::RandFloatMinMax(3.0f, 4.0f);

	//Combat
	damage = 30.0f;
	fireRate = 2.0f;
	animationFSM.SetFireRate(fireRate);
	collisionRadius = 1.0f;
	attackRange = 1.0f;
	attackCooldownTimer = 1.0 / fireRate;	
	cannotSeePlayerTimer = 5.0f;

	//Line Of Sight
	viewAngle = 15.0f;
	viewRange = 10.0f;

	//Alerting
	alertTime = 3.0f;
	alertTimer = alertTime;
	alertRadius = 20.0f;
	alertMesh = MeshBuilder::GetInstance().GenerateQuad("Alert Mesh");
	alertTexture.textureArray[0] = TextureManager::GetInstance().AddTexture("Alert Warning Texture", "Image//Cyborg_Shooter//Characters//Enemies//Alert_Warning.tga");

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
	shouldMove = false;

}

Brawler::~Brawler() {

}

//Movement
void Brawler::Move(const double& deltaTime) {

	Vector2 acceleration;
	acceleration.y += gravity;
	
	if (isMoving) {
		acceleration += GetForwardDirection() * 200.0f;
	}

	//cout << "Brawler Acceleration: " << acceleration << endl;
	velocity += acceleration * deltaTime;
	//cout << "Brawler Velocity(Before): " << velocity << endl;

	//Friction
	float frictionCoefficient = 1.0f;
	float frictionAcceleration = (std::abs(gravity) * frictionCoefficient);
	//cout << "Brawler: Friction Acceleration: " << frictionAcceleration * deltaTime << endl;
	if (std::abs(velocity.x) > Math::EPSILON) {
		if (velocity.x < 0.0f) {
			velocity.x = Math::Min(0.0f, velocity.x + frictionAcceleration * static_cast<float>(deltaTime));
		} else if (velocity.x > 0.0f) {
			velocity.x = Math::Max(0.0f, velocity.x - frictionAcceleration * static_cast<float>(deltaTime));
		}
	}

	//Limit our speed
	this->velocity.x = Math::Clamp(this->velocity.x, -maxSpeed, maxSpeed);
	this->velocity.y = Math::Clamp(this->velocity.y, -27.0f, 27.0f);

	//cout << "Brawler Velocity(After): " << velocity << endl;

	//Y-Axis
	position.y += velocity.y * static_cast<float>(deltaTime);

	canWalkLeft = true;
	canWalkRight = true;
	if (IsOnEdgeLeft()) {
		//cout << "Is On Edge Left" << endl;
		canWalkLeft = false;
	}
	if (IsOnEdgeRight()) {
		//cout << "Is On Edge Right" << endl;
		canWalkRight = false;
	}
	vector<unsigned int> collisionResult = CheckCollisionUp();
	for (unsigned int i = 0; i < collisionResult.size(); ++i) {
		unsigned int terrain = GetTileType(TILE_TYPE::TERRAIN, collisionResult[i]);
		if (terrain != TILE_NOTHING) {
			int tileRow = tileSystem->GetTile(position.y + tileCollider.GetDetectionHeight() * 0.5f);
			position.y = (static_cast<float>(tileRow - 1) + 0.5f) * tileSystem->GetTileSize() - tileCollider.GetDetectionHeight() * 0.5f;
			velocity.y = -velocity.y;
			break;
		}
	}

	collisionResult = CheckCollisionDown();
	onGround = false;
	for (unsigned int i = 0; i < collisionResult.size(); ++i) {
		unsigned int terrain = GetTileType(TILE_TYPE::TERRAIN, collisionResult[i]);
		if (terrain != 0) {
			int tileRow = tileSystem->GetTile(position.y - tileCollider.GetDetectionHeight() * 0.5f);
			position.y = (static_cast<float>(tileRow) + 0.5f) * tileSystem->GetTileSize() + tileCollider.GetDetectionHeight() * 0.5f;
			velocity.y = 0;
			onGround = true;
			break;
		}
	}

	//X-Axis
	position.x += velocity.x * deltaTime;
	if (HitWallLeft()) {
		int tileCol = tileSystem->GetTile(position.x - tileCollider.GetDetectionWidth() * 0.5f);
		position.x = (static_cast<float>(tileCol) + 0.5f) * tileSystem->GetTileSize() + (tileCollider.GetDetectionWidth() * 0.5f);
		velocity.x = 0;
		canWalkLeft = false;
	} else if (HitWallRight()) {
		int tileCol = tileSystem->GetTile(position.x + tileCollider.GetDetectionWidth() * 0.5f);
		position.x = (static_cast<float>(tileCol - 1) + 0.5f) * tileSystem->GetTileSize() - (tileCollider.GetDetectionWidth() * 0.5f);
		velocity.x = 0;
		canWalkRight = false;
	}

}

//Alert
void Brawler::AlertAllies(const double& deltaTime) {

	if (hasAlertedAllies || allies == nullptr) {
		currentState = STATE::COMBAT;
		return;
	}

	isMoving = false;
	if (alertTimer > 0.0f) {
		alertTimer -= static_cast<float>(deltaTime);
	}

	if (alertTimer <= 0.0f) {
		for (set<Enemy*>::iterator iter = (*allies).begin(); iter != (*allies).end(); ++iter) {
			Enemy* allyPtr = *iter;
			if (allyPtr->isDead) {
				continue;
			}
			allyPtr->Alert();
		}
		hasAlertedAllies = true;
	}

}

void Brawler::Alert() {

	if (!isDead) {
		Enemy::Alert();
		currentState = STATE::COMBAT;
	}

}

//Combat
void Brawler::Combat(const double& deltaTime) {

	if (target == nullptr) {
		return;
	}

	if (!CanSeePlayer()) {
		cannotSeePlayerTimer -= static_cast<float>(deltaTime);
	} else {
		cannotSeePlayerTimer = 5.0f;
	}

	if (cannotSeePlayerTimer < 0.0f) {
		currentState = STATE::PATROL;
	}

	float combinedRadius = this->collisionRadius + target->GetCollisionRadius();
	float distanceToTargetSquared = (target->position - position).LengthSquared();
	if (distanceToTargetSquared > combinedRadius * combinedRadius) {
		Chase();
	} else {
		//Face Player
		isMoving = false;
		if (target->position.x < position.x) {
			FaceLeft();
		} else if (target->position.x > position.x) {
			FaceRight();
		}
		Attack();
	}

}

void Brawler::Chase() {
	
	isMoving = false;
	if (target->position.x < position.x) {
		FaceLeft();
		if (canWalkLeft) {
			isMoving = true;
		}
	} else if (target->position.x > position.x) {
		FaceRight();
		if (canWalkRight) {
			isMoving = true;
		}
	}	

}

void Brawler::Attack() {

	isAttacking = true;
	if (attackCooldownTimer <= 0.0f) {
		attackCooldownTimer = 1.0f / fireRate;
		target->TakeDamage(damage);
		cout << "Damaging Player" << endl;
	}

}

bool Brawler::TakeDamage(const int& damage) {

	bool tookDamage = Character::TakeDamage(damage);

	currentState = STATE::COMBAT;
	
	return tookDamage;

}

//Patrol
void Brawler::Patrol(const double& deltaTime) {

	if (CanSeePlayer()) {
		if (hasAlertedAllies || isAlerted) {
			currentState = STATE::COMBAT;
		} else {
			if (Math::RandIntMinMax(1, 5) <= 3) {
				currentState = STATE::COMBAT;
				//currentState = STATE::ALERT;
			} else {
				currentState = STATE::ALERT;
				AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//alert.mp3", false);
			}
		}
		isAlerted = true;
		return;
	}

	patrolTime -= static_cast<float>(deltaTime);
	//Reset our things for this patrol cycle.
	if (patrolTime < 0.0f) {
		patrolTime = Math::RandFloatMinMax(3.0f, 5.0f);
		//Let's decide if we want to walk this cycle.
		if (Math::RandInt() % 2 == 0) {
			shouldMove = true;
		} else {
			shouldMove = false;
		}
		if (Math::RandInt() % 2 == 0) {
			FaceLeft();
		} else {
			FaceRight();
		}
	}

	//Okay, we want to walk. Let's check what our walking options are.
	if (shouldMove) {
		if (!canWalkLeft && canWalkRight) { //We can only walk right.
			FaceRight();
			isMoving = true;
		} else if (canWalkLeft && !canWalkRight) { //We can only walk left.
			FaceLeft();
			isMoving = true;
		} else if (canWalkLeft && canWalkRight) {
			isMoving = true;
		}
	}

}

//Dead
void Brawler::Dead(const double& deltaTime) {

	isMoving = false;
	if (!isDead) {
		isDead = true;
		if (target != nullptr) {
			target->AddScore(150);
		}
	}

}

//Virtual Function(s)
void Brawler::Update(const double& deltaTime) {

	damageCooldown = Math::Max(0.0f, damageCooldown - static_cast<float>(deltaTime));
	if (isAttacking) {
		attackCooldownTimer = Math::Max(0.0f, attackCooldownTimer - static_cast<float>(deltaTime));
	} else {
		attackCooldownTimer = 1.0 / fireRate;
	}
	isAttacking = false;
	isMoving = false;

	if (currentHealth <= 0.0f) {
		currentState = STATE::DEAD;
	}

	switch (currentState) {
		case STATE::PATROL: {
			Patrol(deltaTime);
		}
		break;
		case STATE::ALERT: {
			AlertAllies(deltaTime);
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

	Move(deltaTime);
	animationFSM.SetIsAttacking(isAttacking);
	animationFSM.SetIsDead(isDead);
	animationFSM.SetIsMoving(isMoving);
	animationFSM.Update(deltaTime);

}

void Brawler::Render() {

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

	if (currentState == STATE::ALERT) {
		modelStack.PushMatrix();
			modelStack.Translate(position.x, position.y + 2, 0);
			modelStack.Scale(1.5, 1.5, 1);
			RenderHelper::GetInstance().RenderMesh(*alertMesh, alertTexture, false);
		modelStack.PopMatrix();
	}

	RenderBullets();

}

void Brawler::RenderUI() {
}

void Brawler::Reset() {

	Enemy::Reset();

	cannotSeePlayerTimer = 5.0f;
	currentState = STATE::PATROL;
	patrolTime = 3.0f;
	shouldMove = false;
	
}