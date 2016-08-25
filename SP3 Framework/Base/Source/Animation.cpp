#include "Animation.h"
#include "MyMath.h"

void Animation::Update(const double& deltaTime) {
	
	if (!animActive || animTime < Math::EPSILON || row == 0 || column == 0) {
		return;
	}
	
	this->currentTime += deltaTime;
	
	unsigned int numFrame = 0;
	if (endFrame > startFrame) {
		numFrame = endFrame - startFrame + 1;
	} else {
		numFrame = (row * column) - (startFrame - endFrame) + 1;
	}
	
	double frameTime = animTime / static_cast<float>(numFrame);
	currentFrame = static_cast<unsigned int>(currentTime / frameTime) + startFrame;
	currentFrame %= (row * column);

	if (currentTime > animTime) {
		if (currentFrame != endFrame) {
			currentFrame = endFrame;
		}
		if (loop == false) {
			animActive = false;
		} else {
			Reset(true);
		}
	}

}

void Animation::Reset(bool animActive) {

	currentFrame = startFrame;
	this->animActive = animActive;
	currentTime = 0.0;


}