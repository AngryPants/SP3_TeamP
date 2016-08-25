#include "SpriteAnimation.h"
#include "GL\glew.h"
#include "Vertex.h"

SpriteAnimation::SpriteAnimation(const string& meshName, unsigned int row, unsigned int col) : Mesh(meshName) {//, row(row), column(col) {
}

SpriteAnimation::~SpriteAnimation() {
}

void SpriteAnimation::Update(double deltaTime) {

	if (animation == nullptr) {
		std::cout << name << " has no animation attached." << std::endl;
		return;
	}

	animation->Update(deltaTime);

	/*if (!animation->animActive || animation->animTime < Math::EPSILON || row == 0 || column == 0) {
		return;
	}
	
	this->currentTime += deltaTime;
	
	unsigned int numFrame = 0;
	if (animation->endFrame > animation->startFrame) {
		numFrame = animation->endFrame - animation->startFrame + 1;
	} else {
		numFrame = (row * column) - (animation->startFrame - animation->endFrame) + 1;
	}
	
	double frameTime = animation->animTime / static_cast<float>(numFrame);
	currentFrame = static_cast<unsigned int>(currentTime / frameTime) + animation->startFrame;
	currentFrame %= (row * column);

	if (currentTime > animation->animTime) {
		if (currentFrame != animation->endFrame) {
			currentFrame = animation->endFrame;
		}
		if (animation->loop == false) {
			animation->animActive = false;
		} else {
			Reset(true);
		}
	}*/

}

void SpriteAnimation::Reset(bool animActive) {

	if (animation == nullptr) {
		std::cout << name << " has no animation attached." << std::endl;
	}

	animation->Reset(animActive);

	/*currentFrame = animation->startFrame;
	animation->animActive = true;
	currentTime = 0.0;*/

}

void SpriteAnimation::Render() {

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));

	//glDrawArrays(GL_TRIANGLES, offset, count);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	unsigned int offset = 0;
	if (animation != nullptr) {
		offset = animation->currentFrame;
	}
	if (mode == DRAW_LINES) {
		glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, (void*)(offset * 6 * sizeof(GLuint)));
	} else if (mode == DRAW_TRIANGLE_STRIP) {
		glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (void*)(offset * 6 * sizeof(GLuint)));
	} else {
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(offset * 6 * sizeof(GLuint)));
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glDisableVertexAttribArray(3);

}