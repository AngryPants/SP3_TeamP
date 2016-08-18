#include "Hero.h"

Hero::Hero() {

	mesh = nullptr;

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

		//CHeck if within boundaries

		switch (tileSystem->tiles[tileY][tileX].GetTileValue(Tile::TILE_TYPE::TERRAIN)) 
		{

		}

		Tile* tile = &tileSystem->tiles[tileY][tileX];
		switch (tile->GetTileValue(Tile::TILE_TYPE::ITEM)) 
		{
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