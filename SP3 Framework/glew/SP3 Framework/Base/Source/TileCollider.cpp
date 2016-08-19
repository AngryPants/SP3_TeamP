#include "TileCollider.h"

TileCollider::TileCollider()
:
detectionWidth(1), detectionHeight(1),
lengthWidth(0.9f), lengthHeight(0.9f),
numHotspotsWidth(2), numHotspotsHeight(2)
{
}

TileCollider::~TileCollider()
{
}

void TileCollider::SetDetectionWidth(const float &detectionWidth)
{
	if (detectionWidth < 0.0f)
		this->detectionWidth = 0.0f;
	else
		this->detectionWidth = detectionWidth;
}

float TileCollider::GetDetectionWidth() const
{
	return detectionWidth;
}

void TileCollider::SetDetectionHeight(const float &detectionHeight)
{
	if (detectionHeight < 0.0f)
		this->detectionHeight = 0.0f;
	else
		this->detectionHeight = detectionHeight;
}

float TileCollider::GetDetectionHeight() const
{
	return detectionHeight;
}

float TileCollider::GetHotspotOffsetWidth() const
{
	return lengthWidth / static_cast<float>(numHotspotsWidth - 1);
}

float TileCollider::GetHotspotOffsetHeight() const
{
	return lengthHeight / static_cast<float>(numHotspotsHeight - 1);
}

void TileCollider::SetLengthWidth(const float& lengthWidth)
{
	if (lengthWidth < 0.0f)
		this->lengthWidth = 0.0f;
	else
		this->lengthWidth = lengthWidth;
}

float TileCollider::GetLengthWidth() const
{
	return lengthWidth;
}

void TileCollider::SetLengthHeight(const float& lengthHeight)
{
	if (lengthHeight < 0.0f)
		this->lengthHeight = 0.0f;
	else
		this->lengthHeight = lengthHeight;
}

float TileCollider::GetLengthHeight() const
{
	return lengthHeight;
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