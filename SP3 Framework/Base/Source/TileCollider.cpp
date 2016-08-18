#include "TileCollider.h"

TileCollider::TileCollider() : detectionWidth(0), detectionHeight(0), numHotspotsWidth(0), numHotspotsHeight(0)
{
}

TileCollider::~TileCollider()
{
}

void TileCollider::SetDetectionWidth(const float &detectionWidth)
{
	if (detectionWidth < 0)
		this->detectionWidth = 0;
	else
		this->detectionWidth = detectionWidth;
}

float TileCollider::GetDetectionWidth() const
{
	return detectionWidth;
}

void TileCollider::SetDetectionHeight(const float &detectionHeight)
{
	if (detectionHeight < 0)
		this->detectionHeight = 0;
	else
		this->detectionHeight = detectionHeight;
}

float TileCollider::GetDetectionHeight() const
{
	return detectionHeight;
}

void TileCollider::SetNumHotspotsWidth(const int &numHotspots)
{
	if (numHotspots < 2)
		this->numHotspotsWidth = 2;
	else
		this->numHotspotsWidth = numHotspots;
}

int TileCollider::GetNumHotspotsWidth() const
{
	return numHotspotsWidth;
}

void TileCollider::SetNumHotspotsHeight(const int &numHotspots)
{
	if (numHotspots < 2)
		this->numHotspotsHeight = 2;
	else
		this->numHotspotsHeight = numHotspots;
}

int TileCollider::GetNumHotspotsHeight() const
{
	return numHotspotsHeight;
}

float TileCollider::GetHotspotOffsetWidth() const
{
	return (float)(detectionWidth / numHotspotsWidth - 1);
}

float TileCollider::GetHotspotOffsetHeight() const
{
	return (float)(detectionHeight / numHotspotsHeight - 1);
}