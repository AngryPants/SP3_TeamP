#ifndef AI_STRATEGY_IDLE_H
#define AI_STRATEGY_IDLE_H

#include "AIStrategy.h"

class AIStrategy_Idle : public AIStrategy {
	
public:
	//Constructor(s) & Destructor
	AIStrategy_Idle();
	virtual ~AIStrategy_Idle();

	virtual void Update(AICharacter& ai);

};

#endif