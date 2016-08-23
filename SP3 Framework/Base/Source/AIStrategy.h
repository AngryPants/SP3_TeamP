#ifndef AI_STRATEGY_H
#define AI_STRATEGY_H

class Enemy;

class AIStrategy {

public:
	//Constructor(s) & Destructor
	AIStrategy() {}
	virtual ~AIStrategy() {}

	virtual void Update(Enemy& ai, const double& deltaTime) = 0;

};

#endif