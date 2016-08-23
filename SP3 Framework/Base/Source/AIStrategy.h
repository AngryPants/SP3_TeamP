#ifndef AI_STRATEGY_H
#define AI_STRATEGY_H

class AICharacter;

class AIStrategy {

public:
	//Constructor(s) & Destructor
	AIStrategy() {}
	virtual ~AIStrategy() {}

	virtual void Update(AICharacter& ai) = 0;

};

#endif