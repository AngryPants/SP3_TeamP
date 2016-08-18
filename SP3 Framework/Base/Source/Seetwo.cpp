#include "Seetwo.h"

Seetwo::Seetwo()
{
	health = 150;
}

Seetwo::~Seetwo()
{
}

void Seetwo::Update(const double &deltaTime)
{

}

void Seetwo::Render()
{

}

void Seetwo::RenderUI()
{

}

void Seetwo::Movement(const double &deltaTime)
{

}

void Seetwo::TileCollision()
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