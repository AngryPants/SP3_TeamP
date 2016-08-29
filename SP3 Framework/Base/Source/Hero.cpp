#include "Hero.h"
#include "Enemy.h"
#include "InputManager.h"
#include "TileIndex.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "AudioManager.h"
#include "CollisionSystem.h"

//Constructor(s) & Destructor
Hero::Hero(const string& name, const string& sceneName) : Character(name, sceneName)
{
	//Stats
	lives = 3;
	score = 0;
	abilityScore = 0;
	abilityAvailable = false;
	abilityActive = false;
	abilityAccumulatedTime = 0.0;

	//Movement
	gravity = -20.0f;
	
	//Item Interaction
	canBoost = true;

	//Combat
	damageCooldown = 0.7f;
	damageCooldownTimer = 0.0f;
	enemies = nullptr;	

	//Level Objective
	isAtExit = false;
	
	//Mesh & Textures
	mesh = MeshBuilder::GetInstance().GenerateQuad("Quad");
	healthBarBorder.textureArray[0] = TextureManager::GetInstance().AddTexture("borderHealth", "Image//Cyborg_Shooter//Characters//Heroes//HP_Border.tga");
	borderBackground.textureArray[0] = TextureManager::GetInstance().AddTexture("borderHealth2", "Image//Cyborg_Shooter//Characters//Heroes//BorderBackground.tga");
	healthBarGreen.textureArray[0] = TextureManager::GetInstance().AddTexture("barGreen", "Image//Cyborg_Shooter//Characters//Heroes//HP_BarGreen.tga");
	healthBarYellow.textureArray[0] = TextureManager::GetInstance().AddTexture("barYellow", "Image//Cyborg_Shooter//Characters//Heroes//HP_BarYellow.tga");
	healthBarRed.textureArray[0] = TextureManager::GetInstance().AddTexture("barRed", "Image//Cyborg_Shooter//Characters//Heroes//HP_BarRed.tga");
	abilityBarBorder.textureArray[0] = TextureManager::GetInstance().AddTexture("borderAbility", "Image//Cyborg_Shooter//Characters//Heroes//MP_Border.tga");
	abilityBarCharging.textureArray[0] = TextureManager::GetInstance().AddTexture("barCharging", "Image//Cyborg_Shooter//Characters//Heroes//Ability_BarCharging.tga");
	abilityBarFull.textureArray[0] = TextureManager::GetInstance().AddTexture("barFull", "Image//Cyborg_Shooter//Characters//Heroes//Ability_BarFull.tga");
	lifeCount.textureArray[0] = TextureManager::GetInstance().AddTexture("heart", "Image//Cyborg_Shooter//Characters//Heroes//LifeCount.tga");
	consolas = MeshBuilder::GetInstance().GenerateText("Consolas", 16, 16);
	text.textureArray[0] = TextureManager::GetInstance().AddTexture("text", "Image//Fonts//Consolas.tga");
}

Hero::~Hero() {
}

//Stats
int Hero::GetLives() const
{
	return this->lives;
}

void Hero::SetLives(const int& lives)
{
	this->lives = lives;
}

int Hero::GetScore() const
{
	return this->score;
}

void Hero::SetScore(const int& score)
{
	this->score = score;
}

void Hero::AddScore(const int& score) {

	this->score += score;
	if (!abilityActive)
		AddAbilityScore(score * 0.25);
}

int Hero::GetAbilityScore() const
{
	return abilityScore;
}

void Hero::SetAbilityScore(const int& abilityScore)
{
	this->abilityScore = abilityScore;
}

void Hero::AddAbilityScore(const int& abilityScore)
{
	this->abilityScore += abilityScore;
}

bool Hero::GetAbilityAvailable() const
{
	return abilityAvailable;
}

void Hero::SetAbilityAvailable(const bool& abilityAvailable)
{
	this->abilityAvailable = abilityAvailable;
}

bool Hero::GetAbilityActive() const
{
	return abilityActive;
}

void Hero::SetAbilityActive(const bool& abilityActive)
{
	this->abilityActive = abilityActive;
}

void Hero::SetCheckpoint(int row, int column) {

	this->checkpoint.row = row;
	this->checkpoint.column = column;

}

TileCoord Hero::GetCheckpoint() const {

	return this->checkpoint;

}

//Movement
void Hero::Move(const double& deltaTime) {

	if (tileSystem == nullptr)
	{
		cout << "Unable to update hero as no tileSystem was linked." << endl;
		return;
	}

	Vector2 acceleration;
	//Running
	isMoving = false;
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_RIGHT]) 
	{
		FaceRight();
		acceleration = GetForwardDirection() * 300.0f * InputManager::GetInstance().GetInputInfo().keyValue[INPUT_MOVE_RIGHT];
		isMoving = true;
	} else if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_LEFT]) {
		FaceLeft();
		acceleration = GetForwardDirection() * 300.0f * InputManager::GetInstance().GetInputInfo().keyValue[INPUT_MOVE_LEFT];
		isMoving = true;
	}

	//Jumping
	acceleration.y += gravity;
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_JUMP] && onGround) 
	{
		//acceleration.y += 800.0f;
		velocity.y += 15.0f;
		onGround = false;
	}

	//cout << "Hero Acceleration: " << acceleration << endl;
	this->velocity += acceleration * static_cast<float>(deltaTime);

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

	this->velocity.x = Math::Clamp(this->velocity.x, -maxSpeed, maxSpeed); //Limit our horizontal speed.
	this->velocity.y = Math::Clamp(this->velocity.y, -27.0f, 27.0f);
	//cout << "Hero Velocity: " << this->velocity << endl;

	//Check Y-Axis First
	position.y += velocity.y * static_cast<float>(deltaTime);

	vector<unsigned int> result = CheckCollisionUp();
	for (unsigned int i = 0; i < result.size(); ++i) {
		unsigned int terrain = GetTileType(TILE_TYPE::TERRAIN, result[i]);
		if (terrain != TILE_NOTHING) {
			int tileRow = tileSystem->GetTile(position.y + tileCollider.GetDetectionHeight() * 0.5f);
			position.y = (static_cast<float>(tileRow - 1) + 0.5f) * tileSystem->GetTileSize() - tileCollider.GetDetectionHeight() * 0.5f;
			velocity.y = -velocity.y;
			break;
		}
	}

	result = CheckCollisionDown();
	onGround = false;
	for (unsigned int i = 0; i < result.size(); ++i) {
		unsigned int terrain = GetTileType(TILE_TYPE::TERRAIN, result[i]);
		if (terrain != 0) {
			int tileRow = tileSystem->GetTile(position.y - tileCollider.GetDetectionHeight() * 0.5f);
			position.y = (static_cast<float>(tileRow) + 0.5f) * tileSystem->GetTileSize() + tileCollider.GetDetectionHeight() * 0.5f;
			velocity.y = 0;
			onGround = true;
			break;
		}
	}

	position.x += velocity.x * deltaTime;
	result = CheckCollisionLeft();
	for (unsigned int i = 0; i < result.size(); ++i) {
		unsigned int terrain = GetTileType(TILE_TYPE::TERRAIN, result[i]);
		if (terrain != TILE_NOTHING) {
			int tileCol = tileSystem->GetTile(position.x - tileCollider.GetDetectionWidth() * 0.5f);
			position.x = (static_cast<float>(tileCol) + 0.5f) * tileSystem->GetTileSize() + (tileCollider.GetDetectionWidth() * 0.5f);
			velocity.x = 0;
			break;
		}
	}
	result = CheckCollisionRight();
	for (unsigned int i = 0; i < result.size(); ++i) {
		unsigned int terrain = GetTileType(TILE_TYPE::TERRAIN, result[i]);
		if (terrain != TILE_NOTHING) {
			int tileCol = tileSystem->GetTile(position.x + tileCollider.GetDetectionWidth() * 0.5f);
			position.x = (static_cast<float>(tileCol - 1) + 0.5f) * tileSystem->GetTileSize() - (tileCollider.GetDetectionWidth() * 0.5f);
			velocity.x = 0;
			break;
		}
	}

	//Bounds Checking
	if (position.x < tileSystem->GetBoundaryLeft()) {
		position.x = tileSystem->GetBoundaryLeft();
		velocity.x = 0;
	} else if (position.x > tileSystem->GetBoundaryRight()) {
		position.x = tileSystem->GetBoundaryRight();
		velocity.x = 0;
	}
	if (position.y < tileSystem->GetBoundaryBottom()) {
		position.y = tileSystem->GetBoundaryBottom();
		velocity.y = 0;
	} else if (position.y > tileSystem->GetBoundaryTop()) {
		position.y = tileSystem->GetBoundaryTop();
		velocity.y = 0;
	}
	
}

//Combat
bool Hero::TakeDamage(const int &damage)
{
	if (damageCooldownTimer <= 0.0) {
		currentHealth -= damage;
		damageCooldownTimer = damageCooldown;
		HitSound();
		return true;
	} else {
		return false;
	}	
}

void Hero::HitSound()
{

}

void Hero::SetEnemies(set<Enemy*>* enemies) {
	this->enemies = enemies;
}

void Hero::SpecialAbility(const double &deltaTime)
{
	// Special Ability
	int maxAbilityScore = 50;
	// Stops ability score from exceeding max value
	if (abilityScore > maxAbilityScore)
		abilityScore = maxAbilityScore;

	// Check if ability is active, and makes it available if it is not active and the ability score is greater than 50
	if (!abilityAvailable && !abilityActive && abilityScore >= maxAbilityScore)
	{
		abilityAvailable = true;
	}
	// Sets the ability to active if the 'Z' button is pressed and the ability is available
	if (abilityAvailable && InputManager::GetInstance().GetInputInfo().keyDown[INPUT_ABILITY])
	{
		abilityActive = true;
		abilityAvailable = false;
	}
}

//Item Interaction
void Hero::ItemInteraction(const double& deltaTime) {

	canBoost = true;

	//Check our centre
	ItemInteraction(tileSystem->GetTile(position.y), tileSystem->GetTile(position.x), deltaTime);
		
	//Check Left
	Vector2 hotspot(position.x - tileCollider.GetDetectionWidth() * 0.5f, position.y - tileCollider.GetLengthHeight() * 0.5f);	
	for (int i = 0; i < tileCollider.GetNumHotspotsHeight(); ++i) {		
		ItemInteraction(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x), deltaTime);
		//Update the position of the hotspot.
		hotspot.y += tileCollider.GetHotspotOffsetHeight();
	}

	//Check Right
	hotspot.Set(position.x + tileCollider.GetDetectionWidth() * 0.5f, position.y - tileCollider.GetLengthHeight() * 0.5f);	
	for (int i = 0; i < tileCollider.GetNumHotspotsHeight(); ++i) {		
		ItemInteraction(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x), deltaTime);
		//Update the position of the hotspot.
		hotspot.y += tileCollider.GetHotspotOffsetHeight();
	}

	//Check Down
	hotspot.Set(position.x - tileCollider.GetLengthWidth() * 0.5f, position.y - tileCollider.GetDetectionHeight() * 0.5f);	
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) {		
		ItemInteraction(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x), deltaTime);
		//Update the position of the hotspot.
		hotspot.x += tileCollider.GetHotspotOffsetWidth();
	}

	//Check Up
	hotspot.Set(position.x - tileCollider.GetLengthWidth() * 0.5f, position.y + tileCollider.GetDetectionHeight() * 0.5f);	
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) {		
		ItemInteraction(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x), deltaTime);
		//Update the position of the hotspot.
		hotspot.x += tileCollider.GetHotspotOffsetWidth();
	}

}

void Hero::ItemInteraction(int row, int column, const double& deltaTime) {

	if (row < 0 || row >= tileSystem->GetNumRows()) {
		return;
	} else if (column < 0 || column >= tileSystem->GetNumColumns()) {
		return;
	} else if (tileSystem == nullptr) {
		return;
	}

	unsigned int& tileValue = tileSystem->TileValue(row, column);

	//Items
	unsigned int item = GetTileType(TILE_TYPE::ITEMS, tileValue);
	switch (item) {
		case 0:
			//Do nothing.
		break;
		case TILE_COIN: {
			if (CheckItemToggle(tileValue)) {
				AddScore(10); //Add our score.
				ToggleItem(false, tileValue); //Remove the coin.
				AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Items//Coin_Pickup.flac", false);
			}			
		}
		break;
		case TILE_HEALTH: {
			if (CheckItemToggle(tileValue) && currentHealth < maxHealth) {
				currentHealth += 40;
				ToggleItem(false, tileValue);
			}
		}
		break;
		case TILE_CHECKPOINT: {
			if (CheckItemToggle(tileValue)) {
				checkpoint.Set(row, column);
				ToggleItem(false, tileValue);
				AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Items//Checkpoint.flac", false);
			}
		}
		break;
		case TILE_OBJECTIVE: {
			if (CheckItemToggle(tileValue)) {
				ToggleItem(false, tileValue);
			}
		}
		case TILE_DOOR:
			if (CheckItemToggle(tileValue)) {
				isAtExit = true;
			}
		break;
	}

	unsigned int interactable = GetTileType(TILE_TYPE::INTERACTABLES, tileValue);
	switch (interactable) {
		case TILE_SPIKE: {
			if (TakeDamage(10)) {
				if (velocity.LengthSquared() > Math::EPSILON) {
					Knockback(-velocity.Normalized() * 10);
				} else {
					Knockback(Vector2(1, 0) * 10);
				}
			}
		}
		break;
		case TILE_ACID:
			currentHealth = 0;
		break;
		case TILE_BOOSTPAD_LEFT: {
			if (canBoost) {
				velocity.x -= 100.0f * static_cast<float>(deltaTime);
				canBoost = false;
			}
		}
		break;
		case TILE_BOOSTPAD_RIGHT: {
			if (canBoost) {
				velocity.x += 100.0f * static_cast<float>(deltaTime);
				canBoost = false;
			}
		}
		break;
		case TILE_BOOSTPAD_DOWN: {
			if (canBoost) {
				velocity.y -= 100.0f * static_cast<float>(deltaTime);
				canBoost = false;
			}
		}
		break;
		case TILE_BOOSTPAD_UP: {
			if (canBoost) {
				velocity.y += 100.0f * static_cast<float>(deltaTime);
				canBoost = false;
			}
		}
		break;
	}

}

//Others
void Hero::Respawn() {

	--lives;
	if (lives > 0) {
		position.Set(checkpoint.column * tileSystem->GetTileSize(), checkpoint.row * tileSystem->GetTileSize());
		currentHealth = maxHealth;
		velocity.SetZero();
	} else {
		isDead = true;
	}

}

//Level Objective
bool Hero::IsAtExit() const {

	return isAtExit;

}

//Virtual Function(s)
void Hero::Update(const double &deltaTime) {

	Character::Update(deltaTime);

	isAtExit = false;
	Move(deltaTime);
	ItemInteraction(deltaTime);
	SpecialAbility(deltaTime);
	Attack();
	UpdateBullets(deltaTime);

	if (currentHealth <= 0) {
		Respawn();
	}

}

void Hero::UpdateBullets(const double& deltaTime) {

	for (vector<Bullet*>::iterator bulletIter = bullets.begin(); bulletIter != bullets.end(); ++bulletIter) {
		Bullet* bulletPtr = *bulletIter;
		if (!bulletPtr->isActive) {
			continue;
		}
		bulletPtr->Update(deltaTime);
		//Hurt Enemies
		if (enemies != nullptr) {
			for (set<Enemy*>::iterator enemyIter = (*enemies).begin(); enemyIter != (*enemies).end(); ++enemyIter) {
				Enemy* enemyPtr = *enemyIter;
				if (enemyPtr->isDead) {
					continue;
				}
				float timeToCollision = CollisionSystem::CircleCircle(bulletPtr->position, enemyPtr->position, bulletPtr->radius, enemyPtr->GetCollisionRadius(), bulletPtr->velocity, enemyPtr->velocity);
				if (timeToCollision > 0.0f && timeToCollision <= static_cast<float>(deltaTime)) {
					enemyPtr->TakeDamage(bulletPtr->damage);
					bulletPtr->isActive = false;
					break;
				}
			}
		}
		//Despawn if hit wall
		if (tileSystem != nullptr) {
			TileCoord bulletCoord;
			bulletCoord.Set(tileSystem->GetTile(bulletPtr->position.y), tileSystem->GetTile(bulletPtr->position.x));
			//Check if we are out of the map
			if (bulletCoord.column < 0 || bulletCoord.column >= tileSystem->GetNumColumns()) {
				bulletPtr->isActive = false;
				continue;
			} else if (bulletCoord.row < 0 || bulletCoord.row >= tileSystem->GetNumRows()) {
				bulletPtr->isActive = false;
				continue;
			}
			//Check if we hit a wall
			unsigned int terrain = GetTileType(TILE_TYPE::TERRAIN, tileSystem->TileValue(bulletCoord.row, bulletCoord.column));
			if (terrain != TILE_NOTHING) {
				bulletPtr->isActive = false;
			}
		}
	}

}

void Hero::Render()
{
}

void Hero::RenderUI()
{
	MS& modelStack = GraphicsManager::GetInstance().modelStack;

	// Border Background
	modelStack.PushMatrix();
	modelStack.Translate(-27, 46, 0);
	modelStack.Scale(46, 8, 1);
	RenderHelper::GetInstance().RenderMesh(*mesh, borderBackground, false);
	modelStack.PopMatrix();

	// HP Bar
	float hpBarScale = 34 * (static_cast<float>(currentHealth) / static_cast<float>(maxHealth));
	hpBarScale = Math::Max(0.01f, hpBarScale);
	Math::Clamp(hpBarScale, 0.01f, 34.f);
	if (currentHealth >= maxHealth)
		hpBarScale = 34;
	float hpBarPosition = -50 + hpBarScale * 0.5 + 9;
	
	modelStack.PushMatrix();
	modelStack.Translate(hpBarPosition, 46, 0);
	modelStack.Scale(hpBarScale, 8, 1);
	if (currentHealth >= maxHealth * 0.667)
		RenderHelper::GetInstance().RenderMesh(*mesh, healthBarGreen, false);
	else if (currentHealth >= maxHealth * 0.333)
		RenderHelper::GetInstance().RenderMesh(*mesh, healthBarYellow, false);
	else
		RenderHelper::GetInstance().RenderMesh(*mesh, healthBarRed, false);
	modelStack.PopMatrix();

	// HP Bar Border
	modelStack.PushMatrix();
	modelStack.Translate(-27, 46, 0);
	modelStack.Scale(46, 8, 1);
	RenderHelper::GetInstance().RenderMesh(*mesh, healthBarBorder, false);
	modelStack.PopMatrix();

	// Border Background
	modelStack.PushMatrix();
	modelStack.Translate(-27, 40, 0);
	modelStack.Scale(46, 8, 1);
	RenderHelper::GetInstance().RenderMesh(*mesh, borderBackground, false);
	modelStack.PopMatrix();

	// MP Bar
	float abilityBarScale = 34 * (static_cast<float>(abilityScore) / static_cast<float>(50));
	if (abilityScore >= 50)
		abilityBarScale = 34;
	abilityBarScale = Math::Max(0.01f, abilityBarScale);
	Math::Clamp(abilityBarScale, 0.01f, 34.f);
	float abilityBarPosition = -50 + abilityBarScale * 0.5 + 9;
	
	modelStack.PushMatrix();
	modelStack.Translate(abilityBarPosition, 40, 0);
	modelStack.Scale(abilityBarScale, 8, 1);
	if (!abilityAvailable)
		RenderHelper::GetInstance().RenderMesh(*mesh, abilityBarCharging, false);
	else if (abilityAvailable)
		RenderHelper::GetInstance().RenderMesh(*mesh, abilityBarFull, false);
	modelStack.PopMatrix();
	
	// MP Bar Border
	modelStack.PushMatrix();
	modelStack.Translate(-27, 40, 0);
	modelStack.Scale(46, 8, 1);
	RenderHelper::GetInstance().RenderMesh(*mesh, abilityBarBorder, false);
	modelStack.PopMatrix();

	// Lives
	for (int i = 0; i < lives; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(35 + (5 * i), 45, 0);
		modelStack.Scale(3, 3, 3);
		RenderHelper::GetInstance().RenderMesh(*mesh, lifeCount, false);
		modelStack.PopMatrix();
	}

	// Score
	std::string scoreToString;
	scoreToString = std::to_string(score);

	modelStack.PushMatrix();
	modelStack.Translate(35, 40, 0);
	modelStack.Scale(5, 5, 1);
	RenderHelper::GetInstance().RenderText(*consolas, text, scoreToString, Color(0.831f, 0.686f, 0.215f));
	modelStack.PopMatrix();
}

void Hero::Reset() {

	Character::Reset();
	checkpoint = spawnpoint;
	score = 0;
	lives = 3;
	isAtExit = false;

}