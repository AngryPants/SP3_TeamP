#ifndef MAP_EDITOR_STATE_H
#define MAP_EDITOR_STATE_H

#include "TileSystem.h"

class ME_State {

public:
	//Constructor(s) & Destructor
	ME_State();
	virtual ~ME_State();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();

};

#endif