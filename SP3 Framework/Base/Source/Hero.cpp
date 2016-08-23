#include "Hero.h"
#include "InputManager.h"
#include "TileIndex.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "AudioManager.h"

//Constructor(s) & Destructor
Hero::Hero(const string& name, const string& sceneName) : Character(name, sceneName)
{
	//Stats
	lives = 3;
	score = 0;

	//Movement
	gravity = -20.0f;
	
	//Item Interaction
	canBoost = true;

	//Combat
	enemies = nullptr;

	//Mesh & Textures
	mesh = MeshBuilder::GetInstance().GenerateQuad("Quad");
	healthBarBorder.textureArray[0] = TextureManager::GetInstance().AddTexture("border", "Image//Cyborg_Shooter//Characters//Heroes//HP_Border.tga");
	healthBar.textureArray[0] = TextureManager::GetInstance().AddTexture("bar", "Image//Cyborg_Shooter//Characters//Heroes//HP_Bar.tga");
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

void Hero::SetCheckpoint(int row, int column) {

	this->checkpoint.row = row;
	this->checkpoint.column = column;

}

TileCoord Hero::GetCheckpoint() const {

	return this->checkpoint;

}

/*
void Hero::MoveLeft(const double& deltaTime) {

	//Move Along the X Axis
	position.x += velocity.x * static_cast<float>(deltaTime);

	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x - tileCollider.GetDetectionWidth() * 0.5f, position.y - tileCollider.GetLengthHeight() * 0.5f);
	TileCoord hotspotTile;
	unsigned int terrain = 0;

	//Check for collision against walls.
	for (int i = 0; i < tileCollider.GetNumHotspotsHeight(); ++i) {
		//Which tile our hotspot is in
		hotspotTile.Set(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x));

		//Check if we're within the map's bounds.
		if (hotspotTile.column < 0 || hotspotTile.column >= tileSystem->GetNumColumns()) {
			//Update the position of the hotspot.
			hotspot.y += tileCollider.GetHotspotOffsetHeight();
			continue; //We aren't. Don't bother with this hotspot.
		} else if (hotspotTile.row < 0 || hotspotTile.row >= tileSystem->GetNumRows()) {
			//Update the position of the hotspot.
			hotspot.y += tileCollider.GetHotspotOffsetHeight();
			continue; //We aren't. Don't bother with this hotspot.
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we hit any walls.
		terrain = GetTileInfo(TILE_INFO::TERRAIN, tileSystem->TileValue(hotspotTile.row, hotspotTile.column));
		if (terrain != 0) {
			//Yeah we did. Let's move back to a spot we can be at.
			//position.x += (tileSystem->GetTileSize() * (0.5f + static_cast<float>(hotspotTile.column))) - hotspot.x;
			position.x = (static_cast<float>(hotspotTile.column) + 0.5f) * tileSystem->GetTileSize() + tileCollider.GetDetectionWidth() * 0.5f;
			velocity.x = 0;
			break;
		}

		//Update the position of the hotspot.
		hotspot.y += tileCollider.GetHotspotOffsetHeight();
	}

}

void Hero::MoveRight(const double& deltaTime) {

	//Move Along the X Axis
	position.x += velocity.x * static_cast<float>(deltaTime);

	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x + tileCollider.GetDetectionWidth() * 0.5f, position.y - tileCollider.GetLengthHeight() * 0.5f);
	TileCoord hotspotTile;
	unsigned int terrain = 0;

	//Check for collision against walls or falling through the map.
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) {		
		//Which tile our hotspot is in
		hotspotTile.Set(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x));

		//Check if we're within the map's bounds.
		if (hotspotTile.column < 0 || hotspotTile.column >= tileSystem->GetNumColumns()) {
			//Update the position of the hotspot.
			hotspot.y += tileCollider.GetHotspotOffsetHeight();
			continue; //We aren't. Don't bother with this hotspot.
		} else if (hotspotTile.row < 0 || hotspotTile.row >= tileSystem->GetNumRows()) {
			//Update the position of the hotspot.
			hotspot.y += tileCollider.GetHotspotOffsetHeight();
			continue; //We aren't. Don't bother with this hotspot.
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we hit any walls.
		terrain = GetTileInfo(TILE_INFO::TERRAIN, tileSystem->TileValue(hotspotTile.row, hotspotTile.column));
		if (terrain != 0) {
			//Yeah we did. Let's move back to a spot we can be at.
			position.x = (static_cast<float>(hotspotTile.column - 1) + 0.5f) * tileSystem->GetTileSize() - tileCollider.GetDetectionWidth() * 0.5f;
			velocity.x = 0;
			break;
		}

		//Update the position of the hotspot.
		hotspot.y += tileCollider.GetHotspotOffsetHeight();
	}

}

void Hero::MoveDown(const double& deltaTime) 
{
	//Move Along the Y Axis
	position.y += velocity.y * static_cast<float>(deltaTime);

	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x - tileCollider.GetLengthWidth() * 0.5f, position.y - tileCollider.GetDetectionHeight() * 0.5f);
	TileCoord hotspotTile;
	unsigned int terrain = 0;

	//Check for collision against walls or falling through the map.
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) 
	{
		//Which tile our hotspot is in
		hotspotTile.Set(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x));
		//Check if we're within the map's bounds.
		if (hotspotTile.column < 0 || hotspotTile.column >= tileSystem->GetNumColumns()) {
			//Update the position of the hotspot.
			hotspot.x += tileCollider.GetHotspotOffsetWidth();
			continue; //We aren't. Don't bother with this hotspot.
		} else if (hotspotTile.row < 0 || hotspotTile.row >= tileSystem->GetNumRows()) {
			//Update the position of the hotspot.
			hotspot.x += tileCollider.GetHotspotOffsetWidth();
			continue; //We aren't. Don't bother with this hotspot.
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we hit any walls.
		terrain = GetTileInfo(TILE_INFO::TERRAIN, tileSystem->TileValue(hotspotTile.row, hotspotTile.column));
		if (terrain != 0) {
			//Yeah we did. Let's move back to a spot we can be at.
			position.y = (tileSystem->GetTileSize() * (0.5f + static_cast<float>(hotspotTile.row))) + tileCollider.GetDetectionHeight() * 0.5f;
			velocity.y = 0;
			onGround = true;
			break;
		} else if (velocity.y != 0) {
			onGround = false;
		} else {
			onGround = false;
		}

		//Update the position of the hotspot.
		hotspot.x += tileCollider.GetHotspotOffsetWidth();
	}
}

void Hero::MoveUp(const double& deltaTime) 
{
	//Move Along the Y Axis
	position.y += velocity.y * static_cast<float>(deltaTime);

	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x - tileCollider.GetLengthWidth() * 0.5f, position.y + tileCollider.GetDetectionHeight() * 0.5f);
	unsigned int terrain = 0;
	TileCoord hotspotTile;

	//Check for collision against walls or falling through the map.
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i)
	{		
		//Which tile our hotspot is in
		hotspotTile.Set(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x));

		//Check if we're within the map's bounds.
		if (hotspotTile.column < 0 || hotspotTile.column >= tileSystem->GetNumColumns())
		{			
			//Update the position of the hotspot.
			hotspot.x += tileCollider.GetHotspotOffsetWidth();
			continue; //We aren't. Don't bother with this hotspot.
		}
		else if (hotspotTile.row < 0 || hotspotTile.row >= tileSystem->GetNumRows())
		{
			//Update the position of the hotspot.
			hotspot.x += tileCollider.GetHotspotOffsetWidth();
			continue; //We aren't. Don't bother with this hotspot.
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we hit any walls.
		terrain = GetTileInfo(TILE_INFO::TERRAIN, tileSystem->TileValue(hotspotTile.row, hotspotTile.column));
		if (terrain != 0)
		{
			//Yeah we did. Let's move back to a spot we can be at.
			position.y = (static_cast<float>(hotspotTile.row - 1) + 0.5f) * tileSystem->GetTileSize() - tileCollider.GetDetectionHeight() * 0.5f;
			velocity.y = -velocity.y;
			break;
		}

		//Update the position of the hotspot.
		hotspot.x += tileCollider.GetHotspotOffsetWidth();
	}

}
*/

//Movement
void Hero::Move(const double& deltaTime) {

	if (tileSystem == nullptr)
	{
		cout << "Unable to update hero as no tileSystem was linked." << endl;
		return;
	}

	Vector2 acceleration;
	//Running
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_RIGHT]) 
	{
		acceleration.x += 20.0f * InputManager::GetInstance().GetInputInfo().keyValue[INPUT_MOVE_RIGHT];
		isMoving = true;
		currentDirection = FACING_DIRECTION::RIGHT;
	} 
	else if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_LEFT]) 
	{
		acceleration.x -= 20.0f * InputManager::GetInstance().GetInputInfo().keyValue[INPUT_MOVE_LEFT];		
		isMoving = true;
		currentDirection = FACING_DIRECTION::LEFT;
	} else {
		isMoving = false;
	}

	//Jumping
	acceleration.y += gravity;
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_JUMP] && onGround) 
	{
		onGround = false;
		acceleration.y += 800.0f * InputManager::GetInstance().GetInputInfo().keyValue[INPUT_JUMP];
	}
	
	this->velocity += acceleration * static_cast<float>(deltaTime);
	this->velocity.x = Math::Clamp(this->velocity.x, -maxSpeed, maxSpeed); //Limit our horizontal speed.
	this->velocity.y = Math::Clamp(this->velocity.y, -27.0f, 27.0f);

	position.y += velocity.y * deltaTime;

	vector<unsigned int>& result = CheckCollisionUp();
	for (unsigned int i = 0; i < result.size(); ++i) {
		unsigned int terrain = GetTileInfo(TILE_INFO::TERRAIN, result[i]);
		if (terrain != 0) {
			int tileRow = tileSystem->GetTile(position.y + tileCollider.GetDetectionHeight() * 0.5f);
			position.y = (static_cast<float>(tileRow - 1) + 0.5f) * tileSystem->GetTileSize() - tileCollider.GetDetectionHeight() * 0.5f;
			velocity.y = -velocity.y;
			break;
		}
	}

	result = CheckCollisionDown();
	for (unsigned int i = 0; i < result.size(); ++i) {
		unsigned int terrain = GetTileInfo(TILE_INFO::TERRAIN, result[i]);
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
		unsigned int terrain = GetTileInfo(TILE_INFO::TERRAIN, result[i]);
		if (terrain != 0) {
			int tileCol = tileSystem->GetTile(position.x - tileCollider.GetDetectionWidth() * 0.5f);
			position.x = (static_cast<float>(tileCol) + 0.5f) * tileSystem->GetTileSize() + (tileCollider.GetDetectionWidth() * 0.5f);
			velocity.x = 0;
			break;
			break;
		}
	}
	result = CheckCollisionRight();
	for (unsigned int i = 0; i < result.size(); ++i) {
		unsigned int terrain = GetTileInfo(TILE_INFO::TERRAIN, result[i]);
		if (terrain != 0) {
			int tileCol = tileSystem->GetTile(position.x + tileCollider.GetDetectionWidth() * 0.5f);
			position.x = (static_cast<float>(tileCol - 1) + 0.5f) * tileSystem->GetTileSize() - (tileCollider.GetDetectionWidth() * 0.5f);
			velocity.x = 0;
			break;
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

	if (!isMoving) {
		velocity.x *= static_cast<float>(Math::Clamp(1.0 - deltaTime * 5.0, 0.0, 1.0));
	}

}

//Combat
void Hero::Shoot() {
}

bool Hero::TakeDamage(const int &damage)
{
	if (damageCooldown <= 0.0) {
		currentHealth -= damage;
		damageCooldown = 0.7f;
		return true;
	} else {
		return false;
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
	unsigned int item = GetTileInfo(TILE_INFO::ITEM, tileValue);

	switch (item) {
		case 0:
			//Do nothing.
			break;
		case TILE_COIN: {
			score += 10; //Add our score.
			ClearTileValue(TILE_INFO::ITEM, tileValue); //Remove the coin.
			AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Items//Coin_Pickup.flac", false);
		}
			break;
		case TILE_CHECKPOINT_UNSET: {
			checkpoint.Set(row, column);
			ClearTileValue(TILE_INFO::ITEM, tileValue);
			tileValue |= TILE_CHECKPOINT_SET;
			AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Items//Checkpoint.flac", false);
		}
			break;
		/*case TILE_HERO_SPAWN: {
			if (checkpoint.row != row || checkpoint.column != column) {
				checkpoint.Set(row, column);
				AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Items//Checkpoint.flac", false);
			}
		}*/
			break;
		case TILE_ACID: {
			currentHealth = 0;
		}
			break;
		case TILE_SPIKE: {
			if (TakeDamage(20)) {
				/*velocity.x *= -1;
				velocity.y *= -1;*/
				if (velocity.LengthSquared() > Math::EPSILON)
					Knockback(-velocity.Normalized() * 25);
				else
					Knockback(Vector2(-1, 0) * 25);
			}
		}
			break;
		case TILE_HEALTH: {
			currentHealth += 40;
			ClearTileValue(TILE_INFO::ITEM, tileValue);
		}
			break;
		case TILE_BOOSTPAD_LEFT: {
			if (canBoost) {
				velocity.x -= 200.0f * deltaTime;
				canBoost = false;
			}
		}
			break;
		case TILE_BOOSTPAD_RIGHT: {
			if (canBoost) {
				velocity.x += 200.0f * deltaTime;
				canBoost = false;
			}
		}
			break;
		case TILE_BOOSTPAD_DOWN: {
			if (canBoost) {
				velocity.y -= 200.0f * deltaTime;
				canBoost = false;
			}
		}
			break;
		case TILE_BOOSTPAD_UP: {
			if (canBoost) {
				velocity.y += 200.0f * deltaTime;
				canBoost = false;
			}
		}
			break;
	}

}

//Others
void Hero::Respawn() {

	if (lives > 0) {
		--lives;
		position.Set(checkpoint.column * tileSystem->GetTileSize(), checkpoint.row * tileSystem->GetTileSize());
		currentHealth = maxHealth;
		isActive = true;
	} else {
		isDead = true;
	}

}

//Virtual Function(s)
void Hero::Update(const double &deltaTime)
{	
	Character::Update(deltaTime);

	Move(deltaTime);
	ItemInteraction(deltaTime);
	Shoot();
	
	if (currentHealth <= 0)
	{
		Respawn();
	}
}

void Hero::Render()
{
}

void Hero::RenderUI()
{
	MS& modelStack = GraphicsManager::GetInstance().modelStack;

	float hpBarScale = 34 * (static_cast<float>(currentHealth) / static_cast<float>(maxHealth));
	hpBarScale = Math::Max(0.01f, hpBarScale);
	float hpBarPosition = -50 + hpBarScale * 0.5 + 9;
	modelStack.PushMatrix();
		modelStack.Translate(hpBarPosition, 46, 0);	
		modelStack.Scale(hpBarScale, 8, 1);
		RenderHelper::GetInstance().RenderMesh(*mesh, healthBar, false);
	modelStack.PopMatrix(); 
	
	modelStack.PushMatrix();
		modelStack.Translate(-27, 46, 0);
		modelStack.Scale(46, 8, 1);
		RenderHelper::GetInstance().RenderMesh(*mesh, healthBarBorder, false);
	modelStack.PopMatrix();
	
}