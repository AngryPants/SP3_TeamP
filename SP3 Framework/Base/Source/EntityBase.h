#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H

#include <string>

using std::string;

class EntityBase {

	friend class EntityManager;

private:
	std::string sceneName;
	bool isDestroyed;

public:
	//Variables
	std::string name;

	//Constructor(s) & Destructor
	EntityBase(const std::string& name, const std::string& sceneName);
	virtual ~EntityBase();

	//Function(s)
	void Destroy();
	bool IsDestroyed();
	void SetScene(const string& sceneName);
	const string& GetScene() const;

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();

};

#endif