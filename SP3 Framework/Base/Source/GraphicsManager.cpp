#include "GraphicsManager.h"
#include "Camera.h"
#include <iostream>
#include <map>

using namespace std;

//Constructor(s) & Destructor
GraphicsManager::GraphicsManager() {

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	SetBackgroundColor(0.0f, 0.0f, 0.4f, 0.0f);
	Enable<MODE::CULLING>();
	Enable<MODE::BLENDING>();
	Disable<MODE::WIREFRAME>();
	Enable<MODE::DEPTH_TEST>();
	
	activeShader = nullptr;
	modelStack.LoadIdentity();
	viewStack.LoadIdentity();
	projectionStack.LoadIdentity();

}

GraphicsManager::~GraphicsManager() {

	ClearShaders();
	glDeleteVertexArrays(1, &vertexArrayID);

}

//Private Function(s)
ShaderProgram* GraphicsManager::GetShader(const string& shaderName) {

	ShaderMap::iterator mapIter = shaderMap.find(shaderName);
	if (mapIter == shaderMap.end()) {
		return nullptr;
	}

	return mapIter->second;

}

bool GraphicsManager::ClearShaders() {

	activeShader = nullptr;

	while (shaderMap.size() > 0) {
		if (shaderMap.begin()->second != nullptr) {
			delete shaderMap.begin()->second;
		}
		shaderMap.erase(shaderMap.begin());
	}

	return true;

}

//MVP
void GraphicsManager::SetToCameraView(Camera& camera) {

	modelStack.LoadIdentity();
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z,
					 camera.GetTarget().x,
					 camera.GetTarget().y,
					 camera.GetTarget().z,
					 camera.GetUp().x, camera.GetUp().y, camera.GetUp().z);

	if (camera.IsOrtho()) {
		Mtx44 orthoMatrix;
		orthoMatrix.SetToOrtho(-camera.GetOrthoWidth(), camera.GetOrthoWidth(),
							   -camera.GetOrthoSize(), camera.GetOrthoSize(),
							   camera.GetNearClippingPlane(), camera.GetFarClippingPlane());
		
		projectionStack.LoadMatrix(orthoMatrix);
	} else {
		Mtx44 perspMatrix;
		perspMatrix.SetToPerspective(camera.GetFOV(),
									 camera.aspectRatio.GetRatio(),
									 camera.GetNearClippingPlane(),
									 camera.GetFarClippingPlane());

		projectionStack.LoadMatrix(perspMatrix);
	}

}

void GraphicsManager::SetToHUD(float left, float right, float down, float up, float near, float far) {

	modelStack.LoadIdentity();
	viewStack.LoadIdentity();
	Mtx44 orthoMatrix;
	orthoMatrix.SetToOrtho(left, right, down, up, near, far);
	projectionStack.LoadMatrix(orthoMatrix);

}

//Shader
bool GraphicsManager::HasShader(const string& shaderName) const {

	return shaderMap.count(shaderName) != 0;

}

bool GraphicsManager::SetActiveShader(const string& shaderName) {

	activeShader = GetShader(shaderName);
	if (activeShader == nullptr) {
		cout << "Unable to set " << shaderName << "as active shader as it does not exist in GraphicsManager. The current active shader is now NULL." << endl;
		return false;
	}

	glUseProgram(activeShader->GetProgramID());

	return true;

}

bool GraphicsManager::AddShader(const string& shaderName, const string& vertexShader, const string& fragmentShader) {

	//Check if we already have a shader by this name.
	if (HasShader(shaderName)) {
		cout << "Unable to add shader as a shader by this name already exist." << endl;
		return false;
	}

	ShaderProgram* shaderProgram = new ShaderProgram(shaderName);
	shaderProgram->SetShader(vertexShader, fragmentShader);
	shaderMap.insert(pair<string, ShaderProgram*>(shaderName, shaderProgram));

	cout << shaderName << " has been successfully added to the GraphicsManager." << endl;

	return true;

}

bool GraphicsManager::RemoveShader(const string& shaderName) {

	ShaderMap::iterator mapIter = shaderMap.find(shaderName);
	if (mapIter == shaderMap.end()) {
		cout << "Unable tp remove shader " << shaderName << " as it does not exist in GraphicsManager." << endl;
		return false;
	}

	if (mapIter->second != nullptr) {
		delete mapIter->second;
	}
	shaderMap.erase(mapIter);

	return true;

}

ShaderProgram* GraphicsManager::GetActiveShader() {

	return this->activeShader;

}

//Others
void GraphicsManager::Update() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GraphicsManager::SetBackgroundColor(float red, float green, float blue, float alpha) {

	glClearColor(red, green, blue, alpha);

}