#pragma once
#ifndef TILE_COLLIDER_H
#define TILE_COLLIDER_H

#include "Vector2.h"

class TileCollider
{
private:
	/*
				 H
				 E
				 I
				 G
				 H
				 T
	****J********K********L****
	*************^*************
	A************|************D
	*************|*************
	*************|*************
	B************X----------->E Width
	***************************
	***************************
	C*************************F
	***************************
	****G********H********I****
		<-Offset->
		<---LengthWidth--->
	*/

	float detectionWidth; //See above
	float detectionHeight; //See above
	float lengthWidth; //See above
	float lengthHeight; //See above

	int numHotspotsWidth; // Number of hotspots on Width
	int numHotspotsHeight; // Number of hotspots on Height
	
public:
	TileCollider();
	virtual ~TileCollider();

	void SetDetectionWidth(const float& detectionWidth);
	float GetDetectionWidth() const;	
	void SetDetectionHeight(const float& detectionHeight);
	float GetDetectionHeight() const;

	float GetHotspotOffsetWidth() const; //The distance between hotspots
	float GetHotspotOffsetHeight() const; //The distance between hotspots

	void SetLengthWidth(const float& lengthWidth);
	float GetLengthWidth() const;
	void SetLengthHeight(const float& lengthHeight);
	float GetLengthHeight() const;

	void SetNumHotspotsWidth(const int& numHotspots);
	int GetNumHotspotsWidth() const;
	void SetNumHotspotsHeight(const int& numHotspots);
	int GetNumHotspotsHeight() const;

};

#endif