#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H

#include <string>

using std::string;

class EntityBase {

private:
	bool isDestroyed;

public:
	//Variables
	string name;

	//Constructor(s) & Destructor
	EntityBase(const string& name = "EntityBase") : name(name), isDestroyed(false) {}
	virtual ~EntityBase() {}

	//Function(s)
	bool IsDestroyed() {
		return isDestroyed;
	}
	void Destroy() {
		isDestroyed = true;
	}

	//Virtual Function(s)
	virtual void Update(const double& deltaTime) {}
	virtual void Render() {}
	virtual void RenderUI() {}

};

#endif