/******************************************************************************/
/*!
\file	Kifellah.h
\author Teh Kai Hong Bryan
\par	email: 150587A@mymail.nyp.edu.sg
\brief
Class to define the player character Kifellah
*/
/******************************************************************************/

#pragma once
#ifndef KIFELLAH_H
#define KIFELLAH_H

#include "Hero.h"
#include "AnimationFSM_Kifellah.h"

/******************************************************************************/
/*!
		Class Kifellah:
\brief	Defines Kifellah and their methods
*/
/******************************************************************************/

class Kifellah : public Hero {

private:
	AnimationFSM_Kifellah animationFSM;
	//Mesh & Textures
	Mesh* mesh;
	Texture specialAbility;
public:
	Kifellah(const string& sceneName);
	virtual ~Kifellah();

	void Update(const double &deltaTime);
	void Render();
	void RenderUI();
	void RenderBullets();

	void Movement(const double &deltaTime);
	void TileCollision();

	virtual void Attack();
	virtual void SpecialAbility(const double &deltaTime);
	virtual bool TakeDamage(const int &damage);
	virtual void HitSound();
};

#endif