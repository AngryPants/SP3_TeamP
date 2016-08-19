#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "Mesh.h"
#include <vector>
#include "Animation.h"

class SpriteAnimation : public Mesh {

public:	
	//Variable(s)
	unsigned int row, column;
	double currentTime;
	unsigned int currentFrame;

	Animation* animation;

	//Constructor(s) & Destructor
	SpriteAnimation(const string& meshName, unsigned int row, unsigned int column);
	virtual ~SpriteAnimation();

	//Function(s)
	void Update(double deltaTime);
	virtual void Render();

};

#endif