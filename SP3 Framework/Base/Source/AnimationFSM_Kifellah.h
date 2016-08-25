#ifndef ANIMATION_FSM_KIFELLAH_H
#define ANIMATION_FSM_KIFELLAH_H

#include "AnimationFSM.h"
#include "MeshBuilder.h"
#include "TextureManager.h"

class AnimationFSM_Kifellah {

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
	void SetOnGround(bool onGround) {
		this->onGround[STATE_PREVIOUS] = this->onGround[STATE_CURRENT];
		this->onGround[STATE_CURRENT] = onGround;
	}
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
	AnimationFSM_Kifellah() {
		//currentDirection = MOVE_DIRECTION::RIGHT;
		
		for (unsigned int i = 0; i < static_cast<unsigned int>(NUM_STATE); ++i) {
			isMoving[i] = false;
			isShooting[i] = false;
			onGround[i] = true;
			isDead = false;
		}

		InitAnimation();
	}
	~AnimationFSM_Kifellah() {
		mesh = nullptr;
	}

private:
	enum ANIMATION {
		IDLE, //Not Moving, On Ground, Not Shooting.
		RUNNING, //Moving, On Ground, Not Shooting.
		JUMPING, //Moving/Not Moving, Off Ground, Not Shooting.
		SHOOTING, //Not Moving, On Ground, Shooting.
		RUNNING_SHOOTING, //Moving, On Ground, Shooting.		
		JUMPING_SHOOTING, //Moving/Not Moving, Off Ground, Shooting.
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
	bool isDead;
	bool isMoving[NUM_STATE];
	bool isShooting[NUM_STATE];
	bool onGround[NUM_STATE];
	ANIMATION animationState[NUM_STATE];
	//MOVE_DIRECTION currentDirection;

	//Load all our SpriteAnimations, Animations & Textures.
	void InitAnimation() {
		texture.textureArray[0] = TextureManager::GetInstance().AddTexture("Kifellah", "Image//Cyborg_Shooter//Characters//Heroes//Hero_Kifellah.tga");
		mesh = MeshBuilder::GetInstance().GenerateSpriteAnimation("Kifellah", 7, 10);
		mesh->animation = &animation[IDLE];
		animation[IDLE].Set(7, 10, 0, 9, true, 1.0, true);
		animation[RUNNING].Set(7, 10, 10, 19, true, 1.0, true);
		animation[JUMPING].Set(7, 10, 20, 29, false, 1.0, true);
		animation[SHOOTING].Set(7, 10, 30, 34, true, 1.0 / 3.0, true);
		animation[RUNNING_SHOOTING].Set(7, 10, 40, 49, true, 1.0, true);
		animation[JUMPING_SHOOTING].Set(7, 10, 50, 59, true, 1.0, true);
		animation[DEAD].Set(7, 10, 60, 69, false, 1.0, true);
	}

	void UpdateAnimation() {
		//Let's check if we have a mesh in the first place.
		if (mesh == nullptr) {
			return;
		}
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
		} else if (!isMoving[STATE_CURRENT] && onGround[STATE_CURRENT] && !isShooting[STATE_CURRENT]) {
			//cout << "IDLE" << endl;
			animationState[STATE_CURRENT] = IDLE;
		} else if (isMoving[STATE_CURRENT] && onGround[STATE_CURRENT] && !isShooting[STATE_CURRENT]) {
			//cout << "RUNNING" << endl;
			animationState[STATE_CURRENT] = RUNNING;
		} else if (!isMoving[STATE_CURRENT] && onGround[STATE_CURRENT] && isShooting[STATE_CURRENT]) {
			//cout << "SHOOTING" << endl;
			animationState[STATE_CURRENT] = SHOOTING;
		} else if (isMoving[STATE_CURRENT] && onGround[STATE_CURRENT] && isShooting[STATE_CURRENT]) {
			//cout << "RUNNING_SHOOTING" << endl;
			animationState[STATE_CURRENT] = RUNNING_SHOOTING;
		} else if (!onGround[STATE_CURRENT] && !isShooting[STATE_CURRENT]) {
			//cout << "JUMPING" << endl;
			animationState[STATE_CURRENT] = JUMPING;
		} else if (!onGround[STATE_CURRENT] && isShooting[STATE_CURRENT]) {
			//cout << "JUMPING_SHOOTING" << endl;
			animationState[STATE_CURRENT] = JUMPING_SHOOTING;
		}

		mesh->animation = &animation[animationState[STATE_CURRENT]];
		
		//Do we need to reset the animation?
		bool resetAnimation = true;
		//If there was no change in state, then no.
		if (animationState[STATE_PREVIOUS] == animationState[STATE_CURRENT]) {
			resetAnimation = false;
		} else {
			//If there was, let's see which state changed into what.
			//If we were at JUMPING, and now JUMPING_SHOOTING, then no.
			if (animationState[STATE_PREVIOUS] == JUMPING && animationState[STATE_CURRENT] == JUMPING_SHOOTING) {
				if (animation[JUMPING].animActive == true) {
					resetAnimation = false;
				}
			} else if (animationState[STATE_CURRENT] == JUMPING && animationState[STATE_PREVIOUS] == JUMPING_SHOOTING) {
				resetAnimation = false;
			}
				
			//Same for the other way around.
			if (animationState[STATE_PREVIOUS] == RUNNING && animationState[STATE_CURRENT] == RUNNING_SHOOTING) { //If we were RUNNING and now RUNNING_SHOOTING, then no.
				resetAnimation = false;
			} else if (animationState[STATE_CURRENT] == RUNNING && animationState[STATE_PREVIOUS] == RUNNING_SHOOTING) { //If we were RUNNING and now RUNNING_SHOOTING, then no.
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