#ifndef ANIMATION_H
#define ANIMATION_H

struct Animation {

public:
	//Variable(s)
	unsigned int startFrame;
	unsigned int endFrame;
	bool loop;
	double animTime;
	bool animActive;

	//Constructor(s) & Destructor
	Animation(unsigned int startFrame = 0, unsigned int endFrame = 0, bool loop = false, double animTime = 0.0, bool animActive = false) {
		Set(startFrame, endFrame, loop, animTime, animActive);
	}
	virtual ~Animation() {}

	//Setter(s)
	void Set(unsigned int startFrame, unsigned int endFrame, bool loop, double animTime, bool animActive) {
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->loop = loop;
		this->animTime = animTime;
		this->animActive = animActive;
	}

};

#endif