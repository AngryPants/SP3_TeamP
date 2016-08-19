#include "Hero.h"
#include "InputManager.h"
#include "TileIndex.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "AudioManager.h"

Hero::Hero()
{
	lives = 3;
	score = 0;
	gravity = -20.0f;
	checkpointCol = 2;
	checkpointRow = 4;
	damageTaken = false;
	damageTimer = 0;
	hitTrampoline = false;
}

Hero::~Hero()
{
}

void Hero::Update(const double &deltaTime)
{
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
	} 
	else if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_LEFT]) 
	{
		acceleration.x -= 20.0f * InputManager::GetInstance().GetInputInfo().keyValue[INPUT_MOVE_LEFT];
	}

	//Jumping
	acceleration.y += gravity;
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_JUMP] && onGround) 
	{
		onGround = false;
		acceleration.y += 800.0f * InputManager::GetInstance().GetInputInfo().keyValue[INPUT_JUMP];
	}
	if (hitTrampoline)
	{
		onGround = false;
		acceleration.y += 1600;
		hitTrampoline = false;
	}
	
	this->velocity += acceleration * deltaTime;
	this->velocity.x = Math::Clamp(this->velocity.x, -speed, speed); //Limit our horizontal speed.
	this->velocity.y = Math::Clamp(this->velocity.y, -27.0f, 27.0f);

	/*
	//Collision Checking
	//Find out the size difference between the tiles and us.
	Vector2 sizeDiff;
	sizeDiff.x = tileSystem->GetTileSize() - scale.x;
	sizeDiff.y = tileSystem->GetTileSize() - scale.y;
	//Position of the hotspot we're checking.
	Vector2 hotspotPosition;
	//Which tile our hotspot is in
	int tileX = 0;
	int tileY = 0;

	//Left
	float minY = position.y - tileCollider.GetDetectionHeight() * 0.5f; //Lowest position for our hotspots.
	for (int i = 0; i < tileCollider.GetNumHotspotsHeight(); i++)
	{
		//Find out the position of our hotspot.
		hotspotPosition.x = position.x - tileCollider.GetDetectionWidth() * 0.5f;
		hotspotPosition.y = minY + i * tileCollider.GetHotspotOffsetHeight();
		
		//Make sure our hotspot is within the map boundaries
		if (hotspotPosition.x < tileSystem->GetLeftBorder()) {
			position.x = tileSystem->GetLeftBorder() + scale.x * 0.5f;
			continue;
		}

		//Find out which tile our hotspot is in.
		tileX = tileSystem->GetTile(hotspotPosition.x);
		tileY = tileSystem->GetTile(hotspotPosition.y);

		Tile* tile = &tileSystem->tiles[tileY][tileX];

		if (hotspotPosition.x < tileSystem->GetLeftBorder())
			position.x = tileX * tileSystem->GetTileSize() + sizeDiff.x * 0.5f;

		switch (tile->GetTileValue(Tile::TILE_TYPE::TERRAIN))
		{
			case TILE_WALL_1:
				position.x = tileX * tileSystem->GetTileSize() + sizeDiff.x * 0.5f;
				break;
			case TILE_WALL_2:
				position.x = tileX * tileSystem->GetTileSize() + sizeDiff.x * 0.5f;
				break;
			case TILE_WALL_3:
				position.x = tileX * tileSystem->GetTileSize() + sizeDiff.x * 0.5f;
				break;
		}

		switch (tile->GetTileValue(Tile::TILE_TYPE::ITEM))
		{
			case TILE_COIN:
				tile->ClearTileValue(Tile::TILE_TYPE::ITEM);
				score++;
				break;
			case TILE_CHECKPOINT_UNSET:
				tile->ClearTileValue(Tile::TILE_TYPE::ITEM);
				tile->tileValue |= TILE_CHECKPOINT_SET;
				break;		
		}
	}
	// Right
	for (int i = 0; i < tileCollider.GetNumHotspotsHeight(); i++)
	{
		int minY = position.y - tileCollider.GetDetectionHeight() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = position.x + tileCollider.GetDetectionWidth() * 0.5f;
		hotspotPosition.y = minY + i * tileCollider.GetHotspotOffsetHeight();

		int tileX = tileSystem->GetTile(hotspotPosition.x);
		int tileY = tileSystem->GetTile(hotspotPosition.y);

		Tile* tile = &tileSystem->tiles[tileY][tileX];

		Vector2 sizeDiff;
		sizeDiff.x = tileSystem->GetTileSize() - scale.x;
		sizeDiff.y = tileSystem->GetTileSize() - scale.y;

		if (hotspotPosition.x > tileSystem->GetRightBorder())
			position.x = tileX * tileSystem->GetTileSize() + sizeDiff.x * 0.5f;

		switch (tile->GetTileValue(Tile::TILE_TYPE::TERRAIN))
		{
		case TILE_WALL_1:
		{
			position.x = tileX * tileSystem->GetTileSize() + sizeDiff.x * 0.5f;
			break;
		}
		case TILE_WALL_2:
		{
			position.x = tileX * tileSystem->GetTileSize() + sizeDiff.x * 0.5f;
			break;
		}
		case TILE_WALL_3:
		{
			position.x = tileX * tileSystem->GetTileSize() + sizeDiff.x * 0.5f;
			break;
		}
		}

		switch (tile->GetTileValue(Tile::TILE_TYPE::ITEM))
		{
		case TILE_COIN:
		{
			tile->ClearTileValue(Tile::TILE_TYPE::ITEM);
			score++;
			break;
		}
		case TILE_CHECKPOINT_UNSET:
		{
			tile->ClearTileValue(Tile::TILE_TYPE::ITEM);
			tile->tileValue |= TILE_CHECKPOINT_SET;
			break;
		}
		}
	}

	// Up
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); i++)
	{
		int minX = position.x - tileCollider.GetDetectionWidth() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = minX + i * tileCollider.GetHotspotOffsetWidth();
		hotspotPosition.y = position.y + tileCollider.GetDetectionHeight() * 0.5f;

		int tileX = tileSystem->GetTile(hotspotPosition.x);
		int tileY = tileSystem->GetTile(hotspotPosition.y);

		Tile* tile = &tileSystem->tiles[tileY][tileX];

		Vector2 sizeDiff;
		sizeDiff.x = tileSystem->GetTileSize() - scale.x;
		sizeDiff.y = tileSystem->GetTileSize() - scale.y;

		if (hotspotPosition.y > tileSystem->GetTopBorder())
			position.y = tileY * tileSystem->GetTileSize() + sizeDiff.y * 0.5f;

		switch (tile->GetTileValue(Tile::TILE_TYPE::TERRAIN))
		{
		case TILE_WALL_1:
		{
			position.y = tileY * tileSystem->GetTileSize() + sizeDiff.y * 0.5f;
			break;
		}
		case TILE_WALL_2:
		{
			position.y = tileY * tileSystem->GetTileSize() + sizeDiff.y * 0.5f;
			break;
		}
		case TILE_WALL_3:
		{
			position.y = tileY * tileSystem->GetTileSize() + sizeDiff.y * 0.5f;
			break;
		}
		}

		switch (tile->GetTileValue(Tile::TILE_TYPE::ITEM))
		{
		case TILE_COIN:
		{
			tile->ClearTileValue(Tile::TILE_TYPE::ITEM);
			score++;
			break;
		}
		case TILE_CHECKPOINT_UNSET:
		{
			tile->ClearTileValue(Tile::TILE_TYPE::ITEM);
			tile->tileValue |= TILE_CHECKPOINT_SET;
			break;
		}
		}
	}
	// Down
	for (int i = 0; i < tileCollider.GetNumHotspotsHeight(); i++)
	{
		int minX = position.x - tileCollider.GetDetectionWidth() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = minX + i * tileCollider.GetHotspotOffsetWidth();
		hotspotPosition.y = position.y - tileCollider.GetDetectionHeight() * 0.5f;

		int tileX = tileSystem->GetTile(hotspotPosition.x);
		int tileY = tileSystem->GetTile(hotspotPosition.y);

		Tile* tile = &tileSystem->tiles[tileY][tileX];

		Vector2 sizeDiff;
		sizeDiff.x = tileSystem->GetTileSize() - scale.x;
		sizeDiff.y = tileSystem->GetTileSize() - scale.y;

		if (hotspotPosition.y < tileSystem->GetBottomBorder())
			position.y = tileY * tileSystem->GetTileSize() + sizeDiff.y * 0.5f;

		switch (tile->GetTileValue(Tile::TILE_TYPE::TERRAIN))
		{
		case TILE_WALL_1:
		{
			position.y = tileY * tileSystem->GetTileSize() + sizeDiff.y * 0.5f;
			break;
		}
		case TILE_WALL_2:
		{
			position.y = tileY * tileSystem->GetTileSize() + sizeDiff.y * 0.5f;
			break;
		}
		case TILE_WALL_3:
		{
			position.y = tileY * tileSystem->GetTileSize() + sizeDiff.y * 0.5f;
			break;
		}
		}

		switch (tile->GetTileValue(Tile::TILE_TYPE::ITEM))
		{
		case TILE_COIN:
		{
			tile->ClearTileValue(Tile::TILE_TYPE::ITEM);
			score++;
			break;
		}
		case TILE_CHECKPOINT_UNSET:
		{
			tile->ClearTileValue(Tile::TILE_TYPE::ITEM);
			tile->tileValue |= TILE_CHECKPOINT_SET;
			break;
		}
		}
	}
	*/

	//Move Along Y-Axis
	if (velocity.y > 0) 
	{
		MoveUp(deltaTime);
	} 
	else 
	{
		MoveDown(deltaTime);
	}

	//Move along X-Axis
	if (velocity.x > 0) 
	{
		MoveRight(deltaTime);
	} 
	else 
	{
		MoveLeft(deltaTime);
	}

	//Bounds Checking
	if (position.x < tileSystem->GetBoundaryLeft()) 
	{
		position.x = tileSystem->GetBoundaryLeft();
		velocity.x = 0;
	} 
	else if (position.x > tileSystem->GetBoundaryRight()) 
	{
		position.x = tileSystem->GetBoundaryRight();
		velocity.x = 0;
	}
	if (position.y < tileSystem->GetBoundaryBottom()) 
	{
		position.y = tileSystem->GetBoundaryBottom();
		velocity.y = 0;
	} 
	else if (position.y > tileSystem->GetBoundaryTop()) 
	{
		position.y = tileSystem->GetBoundaryTop();
		velocity.y = 0;
	}

	velocity.x *= (1.0 - deltaTime * 3.0f);

	if (damageTaken)
	{
		damageTimer += deltaTime;
	}
	if (damageTimer > 2)
	{
		damageTaken = false;
	}
}

void Hero::Render()
{
}

void Hero::RenderUI()
{
}

int Hero::GetLives() const
{
	return this->lives;
}

void Hero::SetLives(const int& lives)
{
	this->lives = lives;
}

void Hero::MoveLeft(const double& deltaTime) 
{
	//What is the tile coordinates of our hero now?
	int currentCol = tileSystem->GetTile(position.x);
	int currentRow = tileSystem->GetTile(position.y);
	
	//Which tile our hotspot is in
	int hotspotTileCol = 0;
	int hotspotTileRow = 0;

	//The type of things in the tile
	int terrain = 0;
	int item = 0;

	//Move Along the X Axis
	position.x += velocity.x * deltaTime;

	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x - tileCollider.GetDetectionWidth() * 0.5f, position.y - tileCollider.GetLengthHeight() * 0.5f);

	//Check for collision against walls or falling through the map.
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) 
	{		
		//Which tile our hotspot is in
		hotspotTileCol = tileSystem->GetTile(hotspot.x);
		hotspotTileRow = tileSystem->GetTile(hotspot.y);

		//Check if we're within the map's bounds.
		if (hotspotTileCol < 0 || hotspotTileCol >= tileSystem->GetNumColumns()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		} 
		else if (hotspotTileRow < 0 || hotspotTileRow >= tileSystem->GetNumRows()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we hit any walls.
		terrain = GetTileInfo(TILE_INFO::TERRAIN, tileSystem->TileValue(hotspotTileRow, hotspotTileCol));
		if (terrain != 0) 
		{
			//Yeah we did. Let's move back to a spot we can be at.
			position.x -= hotspot.x - (hotspotTileCol + 1) * tileSystem->GetTileSize() + tileSystem->GetTileSize() * 0.5f;
			velocity.x = 0;
			break;
		}

		//Update the position of the hotspot.
		hotspot.y += tileCollider.GetHotspotOffsetHeight();
	}

	//Okay now that we are the position we actually should be at.
	//Starting position of the hotspots we're checking.
	hotspot.Set(position.x - tileCollider.GetDetectionWidth() * 0.5f, position.y - tileCollider.GetLengthHeight() * 0.5f);

	//Let's check if we've picked up any items
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) 
	{
		//Which tile our hotspot is in
		hotspotTileCol = tileSystem->GetTile(hotspot.x);
		hotspotTileRow = tileSystem->GetTile(hotspot.y);

		//Check if we're within the map's bounds.
		if (hotspotTileCol < 0 || hotspotTileCol >= tileSystem->GetNumColumns()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		} 
		else if (hotspotTileRow < 0 || hotspotTileRow >= tileSystem->GetNumRows()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we can pick up any item
		ItemInteraction(tileSystem->TileValue(hotspotTileRow, hotspotTileCol), hotspot.x, hotspot.y);

		//Update the position of the hotspot.
		hotspot.y += tileCollider.GetHotspotOffsetHeight();
	}

}

void Hero::MoveRight(const double& deltaTime) 
{
	//What is the tile coordinates of our hero now?
	int currentCol = tileSystem->GetTile(position.x);
	int currentRow = tileSystem->GetTile(position.y);
	
	//Which tile our hotspot is in
	int hotspotTileCol = 0;
	int hotspotTileRow = 0;

	//The type of things in the tile
	int terrain = 0;
	int item = 0;

	//Move Along the X Axis
	position.x += velocity.x * deltaTime;

	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x + tileCollider.GetDetectionWidth() * 0.5f, position.y - tileCollider.GetLengthHeight() * 0.5f);

	//Check for collision against walls or falling through the map.
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) 
	{		
		//Which tile our hotspot is in
		hotspotTileCol = tileSystem->GetTile(hotspot.x);
		hotspotTileRow = tileSystem->GetTile(hotspot.y);

		//Check if we're within the map's bounds.
		if (hotspotTileCol < 0 || hotspotTileCol >= tileSystem->GetNumColumns()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		} 
		else if (hotspotTileRow < 0 || hotspotTileRow >= tileSystem->GetNumRows()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we hit any walls.
		terrain = GetTileInfo(TILE_INFO::TERRAIN, tileSystem->TileValue(hotspotTileRow, hotspotTileCol));
		if (terrain != 0) 
		{
			//Yeah we did. Let's move back to a spot we can be at.
			position.x -= hotspot.x - (hotspotTileCol - 1) * tileSystem->GetTileSize() - tileSystem->GetTileSize() * 0.5f;
			velocity.x = 0;
			break;
		}

		//Update the position of the hotspot.
		hotspot.y += tileCollider.GetHotspotOffsetHeight();
	}

	//Okay now that we are the position we actually should be at.
	//Starting position of the hotspots we're checking.
	hotspot.Set(position.x + tileCollider.GetDetectionWidth() * 0.5f, position.y - tileCollider.GetLengthHeight() * 0.5f);

	//Let's check if we've picked up any items
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) 
	{
		//Which tile our hotspot is in
		hotspotTileCol = tileSystem->GetTile(hotspot.x);
		hotspotTileRow = tileSystem->GetTile(hotspot.y);

		//Check if we're within the map's bounds.
		if (hotspotTileCol < 0 || hotspotTileCol >= tileSystem->GetNumColumns()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		} 
		else if (hotspotTileRow < 0 || hotspotTileRow >= tileSystem->GetNumRows()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we can pick up any item
		ItemInteraction(tileSystem->TileValue(hotspotTileRow, hotspotTileCol), hotspot.x, hotspot.y);

		//Update the position of the hotspot.
		hotspot.y += tileCollider.GetHotspotOffsetHeight();
	}

}

void Hero::MoveDown(const double& deltaTime) 
{
	//What is the tile coordinates of our hero now?
	int currentCol = tileSystem->GetTile(position.x);
	int currentRow = tileSystem->GetTile(position.y);
	
	//Which tile our hotspot is in
	int hotspotTileCol = 0;
	int hotspotTileRow = 0;

	//The type of things in the tile
	int terrain = 0;
	int item = 0;

	//Move Along the Y Axis
	position.y += velocity.y * deltaTime;

	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x - tileCollider.GetLengthWidth() * 0.5f, position.y - tileCollider.GetDetectionHeight() * 0.5f);

	//Check for collision against walls or falling through the map.
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) 
	{
		//Which tile our hotspot is in
		hotspotTileCol = tileSystem->GetTile(hotspot.x);
		hotspotTileRow = tileSystem->GetTile(hotspot.y);

		//Check if we're within the map's bounds.
		if (hotspotTileCol < 0 || hotspotTileCol >= tileSystem->GetNumColumns()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		} 
		else if (hotspotTileRow < 0 || hotspotTileRow >= tileSystem->GetNumRows()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we hit any walls.
		terrain = GetTileInfo(TILE_INFO::TERRAIN, tileSystem->TileValue(hotspotTileRow, hotspotTileCol));
		if (terrain != 0) 
		{
			//Yeah we did. Let's move back to a spot we can be at.
			position.y -= hotspot.y - (hotspotTileRow + 1) * tileSystem->GetTileSize() + tileSystem->GetTileSize() * 0.5f;
			velocity.y = 0;
			onGround = true;
			break;
		}
		else if (velocity.y != 0)
		{
			onGround = false;
		}
		else
		{
			onGround = false;
		}

		//Update the position of the hotspot.
		hotspot.x += tileCollider.GetHotspotOffsetWidth();
	}

	//Okay now that we are the position we actually should be at.
	//Starting position of the hotspots we're checking.
	hotspot.Set(position.x - tileCollider.GetLengthWidth() * 0.5f, position.y - tileCollider.GetDetectionHeight() * 0.5f);

	//Let's check if we've picked up any items
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) 
	{
		//Which tile our hotspot is in
		hotspotTileCol = tileSystem->GetTile(hotspot.x);
		hotspotTileRow = tileSystem->GetTile(hotspot.y);

		//Check if we're within the map's bounds.
		if (hotspotTileCol < 0 || hotspotTileCol >= tileSystem->GetNumColumns()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		} 
		else if (hotspotTileRow < 0 || hotspotTileRow >= tileSystem->GetNumRows()) 
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we can pick up any item
		ItemInteraction(tileSystem->TileValue(hotspotTileRow, hotspotTileCol), hotspot.x, hotspot.y);

		//Update the position of the hotspot.
		hotspot.x += tileCollider.GetHotspotOffsetWidth();
	}
}

void Hero::MoveUp(const double& deltaTime) 
{
	//What is the tile coordinates of our hero now?
	int currentCol = tileSystem->GetTile(position.x);
	int currentRow = tileSystem->GetTile(position.y);
	
	//Which tile our hotspot is in
	int hotspotTileCol = 0;
	int hotspotTileRow = 0;

	//The type of things in the tile
	int terrain = 0;
	int item = 0;

	//Move Along the Y Axis
	position.y += velocity.y * deltaTime;

	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x - tileCollider.GetLengthWidth() * 0.5f, position.y + tileCollider.GetDetectionHeight() * 0.5f);

	//Check for collision against walls or falling through the map.
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i)
	{		
		//Which tile our hotspot is in
		hotspotTileCol = tileSystem->GetTile(hotspot.x);
		hotspotTileRow = tileSystem->GetTile(hotspot.y);

		//Check if we're within the map's bounds.
		if (hotspotTileCol < 0 || hotspotTileCol >= tileSystem->GetNumColumns())
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		}
		else if (hotspotTileRow < 0 || hotspotTileRow >= tileSystem->GetNumRows())
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we hit any walls.
		terrain = GetTileInfo(TILE_INFO::TERRAIN, tileSystem->TileValue(hotspotTileRow, hotspotTileCol));
		if (terrain != 0)
		{
			//Yeah we did. Let's move back to a spot we can be at.
			position.y -= hotspot.y - (hotspotTileRow - 1) * tileSystem->GetTileSize() - tileSystem->GetTileSize() * 0.5f;
			velocity.y = -velocity.y;
			break;
		}

		//Update the position of the hotspot.
		hotspot.x += tileCollider.GetHotspotOffsetWidth();
	}

	//Okay now that we are the position we actually should be at.
	//Starting position of the hotspots we're checking.
	hotspot.Set(position.x - tileCollider.GetLengthWidth() * 0.5f, position.y + tileCollider.GetDetectionHeight() * 0.5f);

	//Let's check if we've picked up any items
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i)
	{
		//Which tile our hotspot is in
		hotspotTileCol = tileSystem->GetTile(hotspot.x);
		hotspotTileRow = tileSystem->GetTile(hotspot.y);

		//Check if we're within the map's bounds.
		if (hotspotTileCol < 0 || hotspotTileCol >= tileSystem->GetNumColumns())
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		}
		else if (hotspotTileRow < 0 || hotspotTileRow >= tileSystem->GetNumRows())
		{
			//We aren't. Don't bother with this hotspot.
			continue;
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we can pick up any item
		ItemInteraction(tileSystem->TileValue(hotspotTileRow, hotspotTileCol), hotspot.x, hotspot.y);

		//Update the position of the hotspot.
		hotspot.x += tileCollider.GetHotspotOffsetWidth();
	}
}

void Hero::TakeDamage(const int &damage)
{
	health -= damage;
	damageTaken = true;
}

void Hero::ItemInteraction(unsigned int& tileValue, float &hotspotX, float &hotspotY)
{
	int item = GetTileInfo(TILE_INFO::ITEM, tileValue);
	switch (item)
	{
		case 0:
			//Do nothing.
			break;
		case TILE_COIN:
			score += 10; //Add our score.
			ClearTileValue(TILE_INFO::ITEM, tileValue); //Remove the coin.
			AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Coin_Pickup.flac", false);
			break;
		case TILE_CHECKPOINT_UNSET:
			checkpointRow = tileSystem->GetTile(hotspotY);
			checkpointCol = tileSystem->GetTile(hotspotX);
			ClearTileValue(TILE_INFO::ITEM, tileValue);
			tileValue |= TILE_CHECKPOINT_SET;
			AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Checkpoint.flac", false);
			break;
		case TILE_ACID:
			health = 0;
			break;
		case TILE_SPIKE:
			if (!damageTaken)
			{
				TakeDamage(20);				
				velocity.x *= -1;
				velocity.y *= -1;
			}
			break;
		case TILE_WRENCH:
			health += 40;
			ClearTileValue(TILE_INFO::ITEM, tileValue);
			break;
		case TILE_TRAMPOLINE:
			hitTrampoline = true;
			break;
	}
}

void Hero::Respawn(const int maxHealth)
{
	if (health <= 0)
		isAlive = false;
	if (lives > 0 && !isAlive)
	{
		lives--;
		position.Set(checkpointCol, checkpointRow);
		health = maxHealth;
		isAlive = true;
	}
	if (lives <= 0)
	{
		//game over
	}
}