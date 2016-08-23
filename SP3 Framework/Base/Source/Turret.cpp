#include "Turret.h"

//Constructor(s) & Destructor
Turret::Turret(const string& sceneName) : Enemy("Turret", sceneName) {

	viewAngle = 15.0f;
	viewRange = 10.0f;
	viewDirection.Set(1, 0);

	alertTime = 5.0f;
	alertRadius = 10.0f;

}

Turret::~Turret() {
}

//Alert
void Turret::AlertAllies(const double& deltaTime) {

	if (allies == nullptr) {
		return;
	}

	if (alertTimeLeft > 0.0f) {
		alertTimeLeft = Math::Max(0.0f, alertTimeLeft - static_cast<float>(deltaTime));
		return;
	}

	for (set<Enemy*>::iterator iter = allies->begin(); iter != allies->end(); ++iter) {
		Enemy* ally = *iter;
		float rangeToAllySquared = (ally->position - position).LengthSquared();
		if (rangeToAllySquared < alertRadius * alertRadius) {
			ally->Alert(); //Alert the allies within range.
		}
	}

}