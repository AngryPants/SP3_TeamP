#ifndef ANIMATION_FSM_TURRET_H
#define ANIMATION_FSM_TURRET_H

#include "AnimationFSM.h"
#include "MeshBuilder.h"
#include "TextureManager.h"

class AnimationFSM_Turret {

public:
	//Enum(s)
	enum class MOVE_DIRECTION {
		LEFT,
		RIGHT,
	};

	//Public Function(s)
	void SetIsShooting(bool isShooting) {
		this->isShooting[STATE_PREVIOUS] = this->isShooting[STATE_CURRENT];
		this->isShooting[STATE_CURRENT] = isShooting;
	}
	void SetFireRate(float fireRate) {
		this->fireRate = fireRate;
		animation[SHOOTING].Set(3, 6, 6, 11, true, 1.0 / fireRate, true);
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
	AnimationFSM_Turret() {
		fireRate = 1.0f;
		for (unsigned int i = 0; i < static_cast<unsigned int>(NUM_STATE); ++i) {
			isShooting[i] = false;
			isDead = false;
		}
		InitAnimation();
	}
	virtual ~AnimationFSM_Turret() {
		mesh = nullptr;
	}

private:
	enum ANIMATION {
		IDLE, //Not Moving, Not Shooting.
		SHOOTING, //Not Moving, Shooting.
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
	float fireRate;
	bool isShooting[NUM_STATE];
	ANIMATION animationState[NUM_STATE];
	//MOVE_DIRECTION currentDirection;

	//Load all our SpriteAnimations, Animations & Textures.
	void InitAnimation() {
		texture.textureArray[0] = TextureManager::GetInstance().AddTexture("Turret", "Image//Cyborg_Shooter//Characters//Enemies//Enemy_Turret.tga");
		mesh = MeshBuilder::GetInstance().GenerateSpriteAnimation("Turret", 3, 6);
		mesh->animation = nullptr;
		animation[IDLE].Set(3, 6, 0, 5, true, 0.5, true);
		animation[SHOOTING].Set(3, 6, 6, 11, true, 1.0 / fireRate, true);
		animation[DEAD].Set(3, 6, 12, 16, false, 0.5, true);
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
			//cout << "TURRET DEAD" << endl;
			animationState[STATE_CURRENT] = DEAD;
		} else if (!isShooting[STATE_CURRENT]) {
			//cout << "TURRET IDLE" << endl;
			animationState[STATE_CURRENT] = IDLE;
		} else if (isShooting[STATE_CURRENT]) {
			//cout << "TURRET SHOOTING" << endl;
			animationState[STATE_CURRENT] = SHOOTING;
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
			if (animationState[STATE_PREVIOUS] == IDLE && animationState[STATE_CURRENT] == SHOOTING) {
				if (animation[IDLE].animActive == true) {
					resetAnimation = false;
				}
			}
			else if (animationState[STATE_CURRENT] == IDLE && animationState[STATE_PREVIOUS] == SHOOTING) {
				resetAnimation = false;
			}

			//Same for the other way around.
			if (animationState[STATE_PREVIOUS] == SHOOTING && animationState[STATE_CURRENT] == IDLE) { //If we were RUNNING and now RUNNING_SHOOTING, then no.
				resetAnimation = false;
			}
			else if (animationState[STATE_CURRENT] == SHOOTING && animationState[STATE_PREVIOUS] == IDLE) { //If we were RUNNING and now RUNNING_SHOOTING, then no.
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