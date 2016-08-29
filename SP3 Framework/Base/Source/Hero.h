#pragma once
#ifndef HERO_H
#define HERO_H

#include "Character.h"
#include "Bullet.h"
#include "InputManager.h"
#include "TileCollider.h"

class Enemy;

class Hero : public Character {

private:
	int abilityScore;
	bool abilityAvailable;
	bool abilityActive;
	double abilityAccumulatedTime;

protected:
	//Stats
	int lives;
	int score;
	
	//Level Objective
	bool isAtExit;

	//Checkpoint
	TileCoord checkpoint;

	//Movement
	virtual void Move(const double& deltaTime);
	
	//Item Interaction
	bool canBoost; //Make sure we don't go too fast on boostpads
	virtual void ItemInteraction(const double& deltaTime);
	virtual void ItemInteraction(int row, int column, const double& deltaTime);

	//Mesh & Textures
	Mesh* mesh;
	Texture healthBarGreen;
	Texture healthBarYellow;
	Texture healthBarRed;
	Texture healthBarBorder;
	Texture abilityBarCharging;
	Texture abilityBarFull;
	Texture abilityBarBorder;

public:
	//Constructor(s) & Destructor
	Hero(const string& name, const string& sceneName);
	virtual ~Hero();

	//Combat
	set<Enemy*>* enemies;
	virtual void Attack() = 0;
	virtual bool TakeDamage(const int &damage);
	virtual void HitSound();
	virtual void SpecialAbility(const double &deltaTime);
	void SetEnemies(set<Enemy*>* enemies);

	//Stats
	int GetLives() const;
	void SetLives(const int& lives);	
	int GetScore() const;
	void SetScore(const int& score);
	void AddScore(const int& score);
	int GetAbilityScore() const;
	void SetAbilityScore(const int& abilityScore);
	void AddAbilityScore(const int& abilityScore);
	bool GetAbilityAvailable() const;
	void SetAbilityAvailable(const bool& abilityAvailable);
	bool GetAbilityActive() const;
	void SetAbilityActive(const bool& abilityActive);

	//Level Objective
	bool IsAtExit() const;

	//Checkpoint
	void SetCheckpoint(int row, int column);
	TileCoord GetCheckpoint() const;
	
	//Others
	void Respawn();

	//Virtual Function(s)
	virtual void Update(const double &deltaTime);
	virtual void UpdateBullets(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();
	virtual void RenderBullets() = 0;
	virtual void Reset();

};

#endif