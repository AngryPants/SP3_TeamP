#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H

#include <string>

using std::string;

class EntityBase {

public:
	//Variables
	string name;
	
	//Constructor(s) & Destructor
	EntityBase(const string& name = "EntityBase") : name(name) {}
	virtual ~EntityBase() {}

	//Virtual Function(s)
	virtual void Update(const double& deltaTime) {}
	virtual void Render() {}
	virtual void RenderUI() {}

};

#endif