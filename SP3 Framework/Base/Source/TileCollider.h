#pragma once
#ifndef TILE_COLLIDER_H
#define TILE_COLLIDER_H

#include "Vector2.h"

class TileCollider
{
private:
	float detectionWidth;
	float detectionHeight;
	int numHotspotsWidth; // Number of hotspots on Width
	int numHotspotsHeight; // Number of hotspots on Height

public:
	TileCollider();
	virtual ~TileCollider();

	void SetDetectionWidth(const float &detectionWidth);
	float GetDetectionWidth() const;
	
	void SetDetectionHeight(const float &detectionHeight);
	float GetDetectionHeight() const;

	void SetNumHotspotsWidth(const int &numHotspots);
	int GetNumHotspotsWidth() const;

	void SetNumHotspotsHeight(const int &numHotspots);
	int GetNumHotspotsHeight() const;

	float GetHotspotOffsetWidth() const;
	float GetHotspotOffsetHeight() const;
};

#endif