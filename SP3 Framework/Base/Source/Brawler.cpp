#include "Brawler.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

//Constructor & Destructor
Brawler::Brawler(const string& sceneName) : Enemy("Brawler", sceneName) {

	//State
	currentState = STATE::PATROL;

	//Health
	maxHealth = 300.0f;
	currentHealth = maxHealth;
	canWalkLeft = true;
	canWalkRight = true;

	//Movement
	isMoving = false;
	maxSpeed = 5.0f;

	//Combat
	damage = 50.0f;
	fireRate = 1.0;
	collisionRadius = 1.0f;

	//Line Of Sight
	viewAngle = 15.0f;
	viewRange = 10.0f;

	//Alerting
	alertTime = 5.0f;
	alertTimer = alertTime;
	alertRadius = 20.0f;

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
	alertTimer = 3.0f;

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
	position.y += velocity.y * deltaTime;

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
		unsigned int terrain = GetTileInfo(TILE_INFO::TERRAIN, collisionResult[i]);
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
		unsigned int terrain = GetTileInfo(TILE_INFO::TERRAIN, collisionResult[i]);
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

}

//Combat

void Brawler::Combat(const double& deltaTime) {
}

void Brawler::Chase() {

}

void Brawler::Attack() {

}

//Patrol
void Brawler::Patrol(const double& deltaTime) {

	if (CanSeePlayer()) {
		//currentState = STATE::COMBAT;
		//return;
	}

	patrolTime -= static_cast<float>(deltaTime);
	//Reset our things for this patrol cycle.
	if (patrolTime < 0.0f) {
		patrolTime = Math::RandFloatMinMax(3.0f, 5.0f);
		//Let's decide if we want to walk this cycle.
		if (Math::RandInt() % 2 == 0) {
			isMoving = true;
		} else {
			isMoving = false;
			//isMoving = true;
		}
		if (Math::RandInt() % 2 == 0) {
			FaceLeft();
		} else {
			FaceRight();
		}
	}

	//Okay, we want to walk. Let's check what our walking options are.
	if (isMoving) {
		if (!canWalkLeft && canWalkRight) { //We can only walk right.
			FaceRight();
		} else if (canWalkLeft && !canWalkRight) { //We can only walk left.
			FaceLeft();
		} else { //We either can walk left or right, or cannot walk either. So fuck it, let's decide at random.
			if (!canWalkLeft && !canWalkRight) { //Since we can't walk left or right, let's not walk;
				isMoving = false;
			}
		}
	}

}

//Dead
void Brawler::Dead(const double& deltaTime) {

	if (!isDead) {
		isDead = true;
		if (target != nullptr) {
			target->AddScore(150);
		}
	}

}

//Virtual Function(s)
void Brawler::Update(const double& deltaTime) {

	Character::Update(deltaTime);	
	Move(deltaTime);
	isAttacking = false;

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
		case STATE::COMBAT: {
			Combat(deltaTime);
		}
		break;
		case STATE::DEAD: {
			Dead(deltaTime);
		}
	}

	animationFSM.SetIsShooting(isAttacking);
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

	RenderBullets();

}

void Brawler::RenderUI() {
}

void Brawler::Reset() {



}