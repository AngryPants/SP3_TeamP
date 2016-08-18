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

		if (hotspotPosition.x < tileSystem->GetLeftBorder())
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
	// Right
	for (int i = 0; i < tCollision.GetNumHotspotsHeight(); i++)
	{
		int minY = position.y - tCollision.GetDetectionHeight() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = position.x + tCollision.GetDetectionWidth() * 0.5f;
		hotspotPosition.y = minY + i * tCollision.GetHotspotOffsetHeight();

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
	for (int i = 0; i < tCollision.GetNumHotspotsWidth(); i++)
	{
		int minX = position.x - tCollision.GetDetectionWidth() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = minX + i * tCollision.GetHotspotOffsetWidth();
		hotspotPosition.y = position.y + tCollision.GetDetectionHeight() * 0.5f;

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
	for (int i = 0; i < tCollision.GetNumHotspotsHeight(); i++)
	{
		int minX = position.x - tCollision.GetDetectionWidth() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = minX + i * tCollision.GetHotspotOffsetWidth();
		hotspotPosition.y = position.y - tCollision.GetDetectionHeight() * 0.5f;

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