#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H

#include <string>

using std::string;

class EntityBase {
	
public:
	//Variables
	string name;
	bool isActive;

	//Constructor(s) & Destructor
	EntityBase(const string& name = "EntityBase") : name(name), isActive(true) {}
	virtual ~EntityBase() {}

	//Virtual Function(s)
	virtual void Update(const double& deltaTime) {}
	virtual void Render() {}
	virtual void RenderUI() {}

};

#endif