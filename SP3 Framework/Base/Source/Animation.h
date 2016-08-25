#ifndef ANIMATION_H
#define ANIMATION_H

struct Animation {

public:
	//Variable(s)
	unsigned int row, column;
	double currentTime;
	unsigned int currentFrame;

	unsigned int startFrame;
	unsigned int endFrame;
	bool loop;
	double animTime;
	bool animActive;

	//Constructor(s) & Destructor
	Animation(unsigned int row = 0, unsigned int col = 0, unsigned int startFrame = 0, unsigned int endFrame = 0, bool loop = false, double animTime = 0.0, bool animActive = false) {
		Set(row, col, startFrame, endFrame, loop, animTime, animActive);
	}
	virtual ~Animation() {}

	//Setter(s)
	void Set(unsigned int row, unsigned int col, unsigned int startFrame, unsigned int endFrame, bool loop, double animTime, bool animActive) {
		this->row = row;
		this->column = col;
		currentTime = 0.0f;
		currentFrame = startFrame;		
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->loop = loop;
		this->animTime = animTime;
		this->animActive = animActive;
	}

	void Update(const double& deltaTime);
	void Reset(bool animActive);

};

#endif