#ifndef AI_CHARACTER_H
#define AI_CHARACTER_H

#include "Character.h"

class AIStrategy;

class AICharacter : public Character {

protected:
	//Combat
	float fieldOfView; //What is this character's field of view?
	float viewRange; //How far can this character see?
	float attackRange; //What is the maximum range this character can attack?

	//Strategy
	AIStrategy* strategy;

public:
	//Constructor(s) & Destructor
	AICharacter(const string& name, const string& sceneName) : Character(name, sceneName) {
		fieldOfView = 45.0f;
		viewRange = 10.0f;
		attackRange = 1.0f;
	}
	virtual ~AICharacter() {}

	//Movement
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;
	virtual void Jump() = 0;

	//Direction
	virtual void FaceLeft() = 0;
	virtual void FaceRight() = 0;
	
	//Combat
	void SetFOV(const float& fieldOfView) {
		this->fieldOfView = fieldOfView;
	}
	float GetFOV() const {
		return this->fieldOfView;
	}
	void SetViewRange(const float& viewRange) {
		this->viewRange = viewRange;
	}
	float GetViewRange() const {
		return this->viewRange;
	}	
	void SetAttackRange(const float& attackRange) {
		this->attackRange = attackRange;
	}
	float GetAttackRange() const {
		return this->attackRange;
	}
	virtual GameEntity* GetTarget() = 0;
	virtual void Attack() = 0;

	//Strategy
	virtual void ChangeStrategy(AIStrategy* strategy) = 0;
	
	//Virtual Function(s)
	void Update(const double& deltaTime) {}
	void Render() {}
	void RenderUI() {}

};

#endif