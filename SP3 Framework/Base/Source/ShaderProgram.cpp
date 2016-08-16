#include "ShaderProgram.h"
#include <GL/glew.h>
#include "shader.hpp"
#include <iostream>
#include "Texture.h"

using std::cout;
using std::endl;

ShaderProgram::ShaderProgram(const string& shaderName) : name(shaderName) {

	programID = 0;

}

ShaderProgram::~ShaderProgram() {

	DeleteShader();

}

ProgramID ShaderProgram::GetProgramID() {

	return this->programID;

}

string ShaderProgram::GetVertexShaderFile() const {

	return this->vertexShader;

}

string ShaderProgram::GetFragmentShaderFile() const {

	return this->fragmentShader;

}

ProgramID ShaderProgram::GetProgramID() {

	return this->programID;

}

UniformID ShaderProgram::GetUniformLocation(const string& uniformName) {

	//Check if we already have the uniform.
	UniformMap::iterator uniformIter = uniformMap.find(uniformName);
	if (uniformIter != uniformMap.end()) {
		return uniformIter->second; //Yeah we do.
	}

	//Nope, FML time to get it then.
	UniformID uniformLocation = glGetUniformLocation(programID, uniformName.c_str());
	uniformMap.insert(std::pair<string, unsigned int>(uniformName, uniformLocation));

	return uniformLocation;

}

bool ShaderProgram::SetShader(const string& vertexShader, const string& fragmentShader) {

	//Check if we already have a prexisting shader. If we do, delete it.
	DeleteShader();

	this->vertexShader = vertexShader;
	this->fragmentShader = fragmentShader;

	programID = LoadShaders(vertexShader.c_str(), fragmentShader.c_str());

	return true;

}

bool ShaderProgram::DeleteShader() {

	if (programID != 0) {
		glDeleteProgram(programID);
	}

	programID = 0;

	return true;

}

bool ShaderProgram::SetActiveTexture(unsigned int index) {

	unsigned int MAX_ACTIVE_TEXTURE = 32;

	if (index >= MAX_ACTIVE_TEXTURE) {
		cout << "Unable to set active texture as texture index is greater than max texture slot of " << MAX_ACTIVE_TEXTURE << endl;
		
		return false;
	}

	glActiveTexture(GL_TEXTURE0 + index);

}

bool ShaderProgram::BindTexture(TextureID textureID) {

	glBindTexture(GL_TEXTURE_2D, textureID);

}

bool ShaderProgram::UnbindTexture() {

	glBindTexture(GL_TEXTURE_2D, 0);

}

//Boolean
void ShaderProgram::UpdateBool(const string& uniformName, bool value) {
	
	if (value) {
		glUniform1i(GetUniformLocation(uniformName), 1);
	} else {
		glUniform1i(GetUniformLocation(uniformName), 0);
	}

}

void ShaderProgram::UpdateBool(const UniformID& uniformID, bool value) {

	if (value) {
		glUniform1i(uniformID, 1);
	} else {
		glUniform1i(uniformID, 0);
	}

}

//Integers
//Get By Name
void ShaderProgram::UpdateInt(const string& uniformName, int value) {

	glUniform1i(GetUniformLocation(uniformName), value);

}

void ShaderProgram::UpdateInt(const string& uniformName, int value1, int value2) {

	glUniform2i(GetUniformLocation(uniformName), value1, value2);

}

void ShaderProgram::UpdateInt(const string& uniformName, int value1, int value2, int value3) {

	glUniform3i(GetUniformLocation(uniformName), value1, value2, value3);

}

void ShaderProgram::UpdateInt(const string& uniformName, int value1, int value2, int value3, int value4) {

	glUniform4i(GetUniformLocation(uniformName), value1, value2, value3, value4);

}

//Get By ID
void ShaderProgram::UpdateInt(const UniformID& uniformID, int value) {

	glUniform1i(uniformID, value);

}

void ShaderProgram::UpdateInt(const UniformID& uniformID, int value1, int value2) {

	glUniform2i(uniformID, value1, value2);

}

void ShaderProgram::UpdateInt(const UniformID& uniformID, int value1, int value2, int value3) {

	glUniform3i(uniformID, value1, value2, value3);

}

void ShaderProgram::UpdateInt(const UniformID& uniformID, int value1, int value2, int value3, int value4) {

	glUniform4i(uniformID, value1, value2, value3, value4);

}

//Get By Name
void ShaderProgram::UpdateIntVector1(const string& uniformName, int* value) {

	glUniform1iv(GetUniformLocation(uniformName), 1, value);

}

void ShaderProgram::UpdateIntVector2(const string& uniformName, int* value) {

	glUniform2iv(GetUniformLocation(uniformName), 1, value);

}

void ShaderProgram::UpdateIntVector3(const string& uniformName, int* value) {

	glUniform3iv(GetUniformLocation(uniformName), 1, value);

}

void ShaderProgram::UpdateIntVector4(const string& uniformName, int* value) {

	glUniform4iv(GetUniformLocation(uniformName), 1, value);

}

//Get By ID
void ShaderProgram::UpdateIntVector1(const UniformID& uniformID, int* value) {

	glUniform1iv(uniformID, 1, value);

}

void ShaderProgram::UpdateIntVector2(const string& uniformName, int* value) {

	glUniform2iv(GetUniformLocation(uniformName), 1, value);

}

void ShaderProgram::UpdateIntVector3(const UniformID& uniformID, int* value) {

	glUniform3iv(uniformID, 1, value);

}

void ShaderProgram::UpdateIntVector4(const UniformID& uniformID, int* value) {

	glUniform4iv(uniformID, 1, value);

}

//Unsigned Integers
//Get By Name
void ShaderProgram::UpdateUInt(const string& uniformName, unsigned int value) {

	glUniform1ui(GetUniformLocation(uniformName), value);

}

void ShaderProgram::UpdateUInt(const string& uniformName, unsigned int value1, unsigned int value2) {

	glUniform2ui(GetUniformLocation(uniformName), value1, value2);

}

void ShaderProgram::UpdateUInt(const string& uniformName, unsigned int value1, unsigned int value2, unsigned int value3) {

	glUniform3ui(GetUniformLocation(uniformName), value1, value2, value3);

}

void ShaderProgram::UpdateUInt(const string& uniformName, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4) {

	glUniform4ui(GetUniformLocation(uniformName), value1, value2, value3, value4);

}

//Get By ID
void ShaderProgram::UpdateUInt(const UniformID& uniformID, unsigned int value) {

	glUniform1ui(uniformID, value);

}

void ShaderProgram::UpdateUInt(const UniformID& uniformID, unsigned int value1, unsigned int value2) {

	glUniform2ui(uniformID, value1, value2);

}

void ShaderProgram::UpdateUInt(const UniformID& uniformID, unsigned int value1, unsigned int value2, unsigned int value3) {

	glUniform3ui(uniformID, value1, value2, value3);

}

void ShaderProgram::UpdateUInt(const UniformID& uniformID, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4) {

	glUniform4ui(uniformID, value1, value2, value3, value4);

}

//Get By Name
void ShaderProgram::UpdateUIntVector1(const string& uniformName, unsigned int* value) {

	glUniform1uiv(GetUniformLocation(uniformName), 1, value);

}

void ShaderProgram::UpdateUIntVector2(const string& uniformName, unsigned int* value) {

	glUniform2uiv(GetUniformLocation(uniformName), 1, value);

}

void ShaderProgram::UpdateUIntVector3(const string& uniformName, unsigned int* value) {

	glUniform3uiv(GetUniformLocation(uniformName), 1, value);

}

void ShaderProgram::UpdateUIntVector4(const string& uniformName, unsigned int* value) {

	glUniform4uiv(GetUniformLocation(uniformName), 1, value);

}

//Get By ID
void ShaderProgram::UpdateUIntVector1(const UniformID& uniformID, unsigned int* value) {

	glUniform1uiv(uniformID, 1, value);

}

void ShaderProgram::UpdateUIntVector2(const UniformID& uniformID, unsigned int* value) {

	glUniform2uiv(uniformID, 1, value);

}

void ShaderProgram::UpdateUIntVector3(const UniformID& uniformID, unsigned int* value) {

	glUniform3uiv(uniformID, 1, value);

}

void ShaderProgram::UpdateUIntVector4(const UniformID& uniformID, unsigned int* value) {

	glUniform4uiv(uniformID, 1, value);

}

//Floats
//Get By Name
void ShaderProgram::UpdateFloat(const string& uniformName, float value) {

	glUniform1f(GetUniformLocation(uniformName), value);

}

void ShaderProgram::UpdateFloat(const string& uniformName, float value1, float value2) {

	glUniform2f(GetUniformLocation(uniformName), value1, value2);

}

void ShaderProgram::UpdateFloat(const string& uniformName, float value1, float value2, float value3) {

	glUniform3f(GetUniformLocation(uniformName), value1, value2, value3);

}

void ShaderProgram::UpdateFloat(const string& uniformName, float value1, float value2, float value3, float value4) {

	glUniform4f(GetUniformLocation(uniformName), value1, value2, value3, value4);

}

//Get By ID
void ShaderProgram::UpdateFloat(const UniformID& uniformID, float value) {

	glUniform1f(uniformID, value);

}

void ShaderProgram::UpdateFloat(const UniformID& uniformID, float value1, float value2) {

	glUniform2f(uniformID, value1, value2);

}

void ShaderProgram::UpdateFloat(const UniformID& uniformID, float value1, float value2, float value3) {

	glUniform3f(uniformID, value1, value2, value3);

}

void ShaderProgram::UpdateFloat(const UniformID& uniformID, float value1, float value2, float value3, float value4) {

	glUniform4f(uniformID, value1, value2, value3, value4);

}

//Get By Name
void ShaderProgram::UpdateFloatVector1(const string& uniformName, float* value) {

	glUniform1fv(GetUniformLocation(uniformName), 1, value);

}

void ShaderProgram::UpdateFloatVector2(const string& uniformName, float* value) {

	glUniform2fv(GetUniformLocation(uniformName), 1, value);

}

void ShaderProgram::UpdateFloatVector3(const string& uniformName, float* value) {

	glUniform3fv(GetUniformLocation(uniformName), 1, value);

}

void ShaderProgram::UpdateFloatVector4(const string& uniformName, float* value) {

	glUniform4fv(GetUniformLocation(uniformName), 1, value);

}

//Get By ID
void ShaderProgram::UpdateFloatVector1(const UniformID& uniformID, float* value) {

	glUniform1fv(uniformID, 1, value);

}

void ShaderProgram::UpdateFloatVector2(const UniformID& uniformID, float* value) {

	glUniform2fv(uniformID, 1, value);

}

void ShaderProgram::UpdateFloatVector3(const UniformID& uniformID, float* value) {

	glUniform3fv(uniformID, 1, value);

}

void ShaderProgram::UpdateFloatVector4(const UniformID& uniformID, float* value) {

	glUniform4fv(uniformID, 1, value);

}

//Get By Name
void ShaderProgram::UpdateFloatMatrix4x4(const string& uniformName, bool transpose, float* value) {

	glUniformMatrix4fv(GetUniformLocation(uniformName), 1, transpose, value);

}

//Get By ID
void ShaderProgram::UpdateFloatMatrix4x4(const UniformID& uniformID, bool transpose, float* value) {

	glUniformMatrix4fv(uniformID, 1, transpose, value);

}