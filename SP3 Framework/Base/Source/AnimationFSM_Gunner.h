#ifndef ANIMATION_FSM_GUNNER_H
#define ANIMATION_FSM_GUNNER_H

#include "AnimationFSM.h"
#include "MeshBuilder.h"
#include "TextureManager.h"

class AnimationFSM_Gunner {

public:
	//Enum(s)
	enum class MOVE_DIRECTION {
		LEFT,
		RIGHT,
	};

	//Public Function(s)
	/*void SetDirection(MOVE_DIRECTION direction) {
	currentDirection = direction;
	}*/
	void SetIsMoving(bool isMoving) {
		this->isMoving[STATE_PREVIOUS] = this->isMoving[STATE_CURRENT];
		this->isMoving[STATE_CURRENT] = isMoving;
	}
	void SetIsShooting(bool isShooting) {
		this->isShooting[STATE_PREVIOUS] = this->isShooting[STATE_CURRENT];
		this->isShooting[STATE_CURRENT] = isShooting;
	}
	/*void SetOnGround(bool onGround) {
		this->onGround[STATE_PREVIOUS] = this->onGround[STATE_CURRENT];
		this->onGround[STATE_CURRENT] = onGround;
	}*/
	void SetIsDead(bool isDead) {
		this->isDead = isDead;
	}

	SpriteAnimation& GetMesh() {
		mesh->animation = &animation[animationState[STATE_CURRENT]];
		return *this->mesh;
	}
	Texture& GetTexture() {
		return this->texture;
	}

	void Update(const double& deltaTime) {
		UpdateAnimation();
		if (mesh != nullptr) {
			mesh->Update(deltaTime);
		}
	}

	//Constructor(s) & Destructor
	AnimationFSM_Gunner() {
		//currentDirection = MOVE_DIRECTION::RIGHT;

		for (unsigned int i = 0; i < static_cast<unsigned int>(NUM_STATE); ++i) {
			isMoving[i] = false;
			isShooting[i] = false;
			//onGround[i] = true;
			isDead = false;
		}

		InitAnimation();
	}
	~AnimationFSM_Gunner() {
		mesh = nullptr;
	}

private:
	enum ANIMATION {
		IDLE, //Not Moving, Not Shooting.
		WALKING, //Not Idle, Not Shooting 
		SHOOTING, //Not Idle, Not Moving, Shooting.
		DEAD,

		NUM_ANIMATION,
	};

	enum SAVED_STATE {
		STATE_CURRENT,
		STATE_PREVIOUS,
		NUM_STATE,
	};

	//Mesh, Animation & Textures
	Animation animation[NUM_ANIMATION];
	SpriteAnimation* mesh;
	Texture texture;

	//Player States
	bool isMoving[NUM_STATE];
	//bool onGround[NUM_STATE];
	bool isShooting[NUM_STATE];
	bool isDead;
	ANIMATION animationState[NUM_STATE];
	//MOVE_DIRECTION currentDirection;

	//Load all our SpriteAnimations, Animations & Textures.
	void InitAnimation() {
		texture.textureArray[0] = TextureManager::GetInstance().AddTexture("Gunner", "Image//Cyborg_Shooter//Characters//Enemies//Enemy_Gunner.tga");
		mesh = MeshBuilder::GetInstance().GenerateSpriteAnimation("Gunner", 4, 9);
		mesh->animation = &animation[IDLE];
		animation[IDLE].Set(4, 9, 0, 5, true, 1.0, true);
		animation[WALKING].Set(4, 9, 9, 17, true, 1.0, true);
		animation[SHOOTING].Set(4, 9, 18, 21, true, 1.0, true);
		animation[DEAD].Set(4, 9, 27, 31, false, 1.0, true);
	}

	void UpdateAnimation() {
		//Let's check if we have a mesh in the first place.
		if (mesh == nullptr) {
			return;
		}
		mesh->animation = nullptr;
		/*
		IDLE, //Not Moving, On Ground, Not Shooting.
		RUNNING, //Moving, On Ground, Not Shooting.
		SHOOTING, //Not Moving, On Ground, Shooting.
		RUNNING_SHOOTING, //Moving, On Ground, Shooting.
		JUMPING, //Moving/Not Moving, Off Ground, Not Shooting.
		JUMPING_SHOOTING, //Moving/Not Moving, Off Ground, Shooting.
		*/

		animationState[STATE_PREVIOUS] = animationState[STATE_CURRENT];

		//Which animation should we be using?
		if (isDead) {
			animationState[STATE_CURRENT] = DEAD;
		} else if (isShooting[STATE_CURRENT]) {
			//cout << "IDLE" << endl;
			
			animationState[STATE_CURRENT] = SHOOTING;
		} else if (isMoving[STATE_CURRENT]) {
			//cout << "RUNNING" << endl;
			animationState[STATE_CURRENT] = WALKING;
		} else {
			//cout << "SHOOTING" << endl;
			animationState[STATE_CURRENT] = IDLE;
		}

		mesh->animation = &animation[animationState[STATE_CURRENT]];

		//Do we need to reset the animation?
		bool resetAnimation = true;
		//If there was no change in state, then no.
		if (animationState[STATE_PREVIOUS] == animationState[STATE_CURRENT]) {
			resetAnimation = false;
		}
		else {
			//If there was, let's see which state changed into what.
			//If we were at JUMPING, and now JUMPING_SHOOTING, then no.
			if (animationState[STATE_PREVIOUS] == WALKING && animationState[STATE_CURRENT] == SHOOTING) {
				if (animation[WALKING].animActive == true) {
					resetAnimation = false;
				}
			}
			else if (animationState[STATE_CURRENT] == WALKING && animationState[STATE_PREVIOUS] == SHOOTING) {
				resetAnimation = false;
			}

			//Same for the other way around.
			if (animationState[STATE_PREVIOUS] == SHOOTING && animationState[STATE_CURRENT] == WALKING) { //If we were RUNNING and now RUNNING_SHOOTING, then no.
				resetAnimation = false;
			}
			else if (animationState[STATE_CURRENT] == SHOOTING && animationState[STATE_PREVIOUS] == WALKING) { //If we were RUNNING and now RUNNING_SHOOTING, then no.
				resetAnimation = false;
			}
		}

		//Reset if we need to.
		if (resetAnimation) {
			mesh->Reset(true);
		}
	}

};

#endif