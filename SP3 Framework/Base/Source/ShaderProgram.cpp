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

UniformID ShaderProgram::GetUniformID(const string& uniformName) {

	return glGetUniformLocation(programID, uniformName.c_str());

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

	return true;

}

bool ShaderProgram::BindTexture(TextureID textureID) {

	glBindTexture(GL_TEXTURE_2D, textureID);

	return true;

}

bool ShaderProgram::UnbindTexture() {

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;

}

//Boolean
void ShaderProgram::Update(const UniformID uniformID, const bool value) {

	glUniform1i(uniformID, value);

}

//Integers
void ShaderProgram::Update(const UniformID uniformID, const int value) {

	glUniform1i(uniformID, value);

}

void ShaderProgram::Update(const UniformID uniformID, const int value1, const int value2) {

	glUniform2i(uniformID, value1, value2);

}

void ShaderProgram::Update(const UniformID uniformID, const int value1, const int value2, const int value3) {

	glUniform3i(uniformID, value1, value2, value3);

}

void ShaderProgram::Update(const UniformID uniformID, const int value1, const int value2, const int value3, const int value4) {

	glUniform4i(uniformID, value1, value2, value3, value4);

}

void ShaderProgram::Update(const UniformID uniformID, const IntVec2& value) {

	glUniform2iv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const IntVec3& value) {

	glUniform3iv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const IntVec4& value) {

	glUniform4iv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const int* value, const unsigned number) {

	glUniform1iv(uniformID, number, value);

}

void ShaderProgram::Update(const UniformID uniformID, const IntVec2& value, const unsigned number) {

	glUniform2iv(uniformID, number, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const IntVec3& value, const unsigned number) {

	glUniform3iv(uniformID, number, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const IntVec4& value, const unsigned number) {

	glUniform4iv(uniformID, number, value.vec);

}

//Unsigned Integers
void ShaderProgram::Update(const UniformID uniformID, const unsigned int value) {

	glUniform1ui(uniformID, value);

}

void ShaderProgram::Update(const UniformID uniformID, const unsigned int value1, const unsigned int value2) {

	glUniform2ui(uniformID, value1, value2);

}

void ShaderProgram::Update(const UniformID uniformID, const unsigned int value1, const unsigned int value2, const unsigned int value3) {

	glUniform3ui(uniformID, value1, value2, value3);

}

void ShaderProgram::Update(const UniformID uniformID, const unsigned int value1, const unsigned int value2, const unsigned int value3, const unsigned int value4) {

	glUniform4ui(uniformID, value1, value2, value3, value4);

}

void ShaderProgram::Update(const UniformID uniformID, const UIntVec2& value) {

	glUniform2uiv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const UIntVec3& value) {

	glUniform3uiv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const UIntVec4& value) {

	glUniform4uiv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const unsigned int* value, const unsigned number) {

	glUniform1uiv(uniformID, number, value);

}

void ShaderProgram::Update(const UniformID uniformID, const UIntVec2& value, const unsigned number) {

	glUniform2uiv(uniformID, number, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const UIntVec3& value, const unsigned number) {

	glUniform3uiv(uniformID, number, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const UIntVec4& value, const unsigned number) {

	glUniform4uiv(uniformID, number, value.vec);

}

//Floats
void ShaderProgram::Update(const UniformID uniformID, const float value) {

	glUniform1f(uniformID, value);

}

void ShaderProgram::Update(const UniformID uniformID, const float value1, const float value2) {

	glUniform2f(uniformID, value1, value2);

}

void ShaderProgram::Update(const UniformID uniformID, const float value1, const float value2, const float value3) {

	glUniform3f(uniformID, value1, value2, value3);

}

void ShaderProgram::Update(const UniformID uniformID, const float value1, const float value2, const float value3, const float value4) {

	glUniform4f(uniformID, value1, value2, value3, value4);

}

void ShaderProgram::Update(const UniformID uniformID, const FloatVec2& value) {

	glUniform2fv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const FloatVec3& value) {

	glUniform3fv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const FloatVec4& value) {

	glUniform4fv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const float* value, const unsigned number) {

	glUniform1fv(uniformID, number, value);

}

void ShaderProgram::Update(const UniformID uniformID, const FloatVec2& value, const unsigned number) {

	glUniform2fv(uniformID, number, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const FloatVec3& value, const unsigned number) {

	glUniform3fv(uniformID, number, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const FloatVec4& value, const unsigned number) {

	glUniform4fv(uniformID, number, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, bool transpose, const FloatMat4x4& value) {

	glUniformMatrix4fv(uniformID, 1, transpose, value.mat);

}

void ShaderProgram::Update(const UniformID uniformID, bool transpose, const FloatMat4x4& value, const unsigned number) {

	glUniformMatrix4fv(uniformID, number, transpose, value.mat);

}

//Doubles
void ShaderProgram::Update(const UniformID uniformID, const double value) {

	glUniform1f(uniformID, value);

}

void ShaderProgram::Update(const UniformID uniformID, const double value1, const double value2) {

	glUniform2f(uniformID, value1, value2);

}

void ShaderProgram::Update(const UniformID uniformID, const double value1, const double value2, const double value3) {

	glUniform3f(uniformID, value1, value2, value3);

}

void ShaderProgram::Update(const UniformID uniformID, const double value1, const double value2, const double value3, const double value4) {

	glUniform4f(uniformID, value1, value2, value3, value4);

}

void ShaderProgram::Update(const UniformID uniformID, const DoubleVec2& value) {

	glUniform2dv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const DoubleVec3& value) {

	glUniform3dv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const DoubleVec4& value) {

	glUniform4dv(uniformID, 1, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const double* value, const unsigned number) {

	glUniform1dv(uniformID, number, value);

}

void ShaderProgram::Update(const UniformID uniformID, const DoubleVec2& value, const unsigned number) {

	glUniform2dv(uniformID, number, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const DoubleVec3& value, const unsigned number) {

	glUniform3dv(uniformID, number, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, const DoubleVec4& value, const unsigned number) {

	glUniform4dv(uniformID, number, value.vec);

}

void ShaderProgram::Update(const UniformID uniformID, bool transpose, const DoubleMat4x4& value) {

	glUniformMatrix4dv(uniformID, 1, transpose, value.mat);

}

void ShaderProgram::Update(const UniformID uniformID, bool transpose, const DoubleMat4x4& value, const unsigned number) {

	glUniformMatrix4dv(uniformID, number, transpose, value.mat);

}