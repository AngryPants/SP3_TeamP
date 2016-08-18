#include "TileCollider.h"

TileCollider::TileCollider() : detectionWidth(0), detectionHeight(0), numHotspots(2), hotspotOffsetWidth(0), hotspotOffsetHeight(0)
{
}

TileCollider::~TileCollider()
{
}

void TileCollider::SetDetectionWidth(const float& detectionWidth)
{
	this->detectionWidth = detectionWidth;
}

float TileCollider::GetDetectionWidth() const
{
	return detectionWidth;
}

void TileCollider::SetDetectionHeight(const float& detectionHeight)
{
	this->detectionHeight = detectionHeight;
}

float TileCollider::GetDetectionHeight() const
{
	return detectionHeight;
}

void TileCollider::SetNumHotspotsWidth(const int& numHotspots)
{
	this->numHotspotsWidth = numHotspots;
}

int TileCollider::GetNumHotspotsWidth() const
{
	return numHotspotsWidth;
}

void TileCollider::SetNumHotspotsHeight(const int& numHotspots)
{
	this->numHotspotsHeight = numHotspots;
}

int TileCollider::GetNumHotspotsHeight() const
{
	return numHotspotsHeight;
}

float TileCollider::GetHotspotOffsetWidth() const
{
	return (float)(detectionWidth / numHotspotsWidth);
}

float TileCollider::GetHotspotOffsetHeight() const
{
	return (float)(detectionHeight / numHotspotsHeight);
}