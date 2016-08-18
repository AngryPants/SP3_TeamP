#include "Daniu.h"

Daniu::Daniu()
{
	damage = 15;
}

Daniu::~Daniu()
{
}

void Daniu::Update(const double &deltaTime)
{

}

void Daniu::Render()
{

}

void Daniu::RenderUI()
{

}

void Daniu::Movement(const double &deltaTime)
{

}

void Daniu::TileCollision()
{
	// Left
	for (int i = 0; i < tCollision.GetNumHotspotsHeight(); i++)
	{
		int minY = position.y - tCollision.GetDetectionHeight() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = position.x - tCollision.GetDetectionWidth() * 0.5f;
		hotspotPosition.y = minY + i * tCollision.GetHotspotOffsetHeight();
		// switch (TileStuff)
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
		hotspotPosition.x = minX + i * tCollision.GetHotspotOffsetWidth;
		hotspotPosition.y = position.y + tCollision.GetDetectionHeight() * 0.5f;

		// switch (TileStuff)
	}
	// Down
	for (int i = 0; i < tCollision.GetNumHotspotsHeight(); i++)
	{
		int minX = position.x - tCollision.GetDetectionWidth() * 0.5f;
		Vector2 hotspotPosition;
		hotspotPosition.x = minX + i * tCollision.GetHotspotOffsetWidth;
		hotspotPosition.y = position.y - tCollision.GetDetectionHeight() * 0.5f;

		// switch (TileStuff)
	}
}