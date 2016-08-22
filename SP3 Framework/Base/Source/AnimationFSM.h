#ifndef ANIMATION_FSM_H
#define ANIMATION_FSM_H

#include "SpriteAnimation.h"
#include "Texture.h"

class AnimationFSM {

public:
	//Variable(s)
	SpriteAnimation* mesh;
	Texture texture;

	//Constructor(s) & Destructor
	AnimationFSM() {
		mesh = nullptr;
	}
	virtual ~AnimationFSM();

	//Function(s)
	virtual void Update(const double& deltaTime) = 0;

};

#endif