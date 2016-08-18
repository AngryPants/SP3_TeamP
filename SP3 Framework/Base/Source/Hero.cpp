#include "Hero.h"

Hero::Hero() : lives(3), score(0)
{
}

Hero::~Hero()
{
}

void Hero::Update(const double &deltaTime)
{
	// Left
	for (int i = 0; i < tCollision.GetNumHotspotsHeight(); i++)
	{
		int minY = position.y - tCollision.GetDetectionHeight() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = position.x - tCollision.GetDetectionWidth() * 0.5f;
		hotspotPosition.y = minY + i * tCollision.GetHotspotOffsetHeight();
		// switch (TileStuff)
		int tileX = tileSystem->GetTile(hotspotPosition.x);
		int tileY = tileSystem->GetTile(hotspotPosition.y);

		Tile* tile = &tileSystem->tiles[tileY][tileX];
		//CHeck if within boundaries
		Vector2 sizeDiff;
		sizeDiff.x = tileSystem->GetTileSize() - scale.x;
		sizeDiff.y = tileSystem->GetTileSize() - scale.y;

		switch (tile->GetTileValue(Tile::TILE_TYPE::TERRAIN)) 
		{
		case TILE_WALL_1:
		{
			position += speed - sizeDiff.x;
			break;
		}
		case TILE_WALL_2:
		{
			position += speed - sizeDiff.x;
			break;
		}
		case TILE_WALL_3:
		{
			position += speed - sizeDiff.x;
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
	// Right
	for (int i = 0; i < tCollision.GetNumHotspotsHeight(); i++)
	{
		int minY = position.y - tCollision.GetDetectionHeight() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = position.x + tCollision.GetDetectionWidth() * 0.5f;
		hotspotPosition.y = minY + i * tCollision.GetHotspotOffsetHeight();

		// switch (TileStuff)
	}
	// Up
	for (int i = 0; i < tCollision.GetNumHotspotsWidth(); i++)
	{
		int minX = position.x - tCollision.GetDetectionWidth() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = minX + i * tCollision.GetHotspotOffsetWidth();
		hotspotPosition.y = position.y + tCollision.GetDetectionHeight() * 0.5f;

		// switch (TileStuff)
	}
	// Down
	for (int i = 0; i < tCollision.GetNumHotspotsHeight(); i++)
	{
		int minX = position.x - tCollision.GetDetectionWidth() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = minX + i * tCollision.GetHotspotOffsetWidth();
		hotspotPosition.y = position.y - tCollision.GetDetectionHeight() * 0.5f;

		// switch (TileStuff)
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