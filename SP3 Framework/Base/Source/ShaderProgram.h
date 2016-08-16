#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <map>

using std::string;
using std::map;
using std::pair;

typedef unsigned int ProgramID;
typedef unsigned int UniformID;
typedef map<string, UniformID> UniformMap;

class ShaderProgram {

private:
	ProgramID programID;
	UniformMap uniformMap;
	string vertexShader, fragmentShader;

	//Enum(s)
	enum class UNIFORM_TYPE {
		U_MVP,
		U_MV,
		U_MV_INVERSE_TRANSPOSE,

		U_LIGHT_ENABLED,
		
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};

public:
	const string name;

	ShaderProgram(const string& name);
	virtual ~ShaderProgram();

	//Vertex Shader & Fragment Shader File
	string GetVertexShaderFile() const;
	string GetFragmentShaderFile() const;

	bool SetShader(const string& vertexShader, const string& fragmentShader);
	bool DeleteShader();
	ProgramID GetProgramID();
	UniformID GetUniformLocation(const string& uniformName);

	//Textures
	bool SetActiveTexture(unsigned int index);
	bool BindTexture(unsigned int textureID);
	bool UnbindTexture();

	//Updating Uniforms (Wow, this is gonna be long...)
	
	//Boolean
	//Get By Name
	void UpdateBool(const string& uniformName, bool value);

	//Get By ID
	void UpdateBool(const UniformID& uniformID, bool value);

	//Integers
	//Get By Name
	void UpdateInt(const string& uniformName, int value);
	void UpdateInt(const string& uniformName, int value1, int value2);
	void UpdateInt(const string& uniformName, int value1, int value2, int value3);
	void UpdateInt(const string& uniformName, int value1, int value2, int value3, int value4);

	//Get By ID
	void UpdateInt(const UniformID& uniformID, int value);
	void UpdateInt(const UniformID& uniformID, int value1, int value2);
	void UpdateInt(const UniformID& uniformID, int value1, int value2, int value3);
	void UpdateInt(const UniformID& uniformID, int value1, int value2, int value3, int value4);

	//Get By Name
	void UpdateIntVector1(const string& uniformName, int* value);
	void UpdateIntVector2(const string& uniformName, int* value);
	void UpdateIntVector3(const string& uniformName, int* value);
	void UpdateIntVector4(const string& uniformName, int* value);

	//Get By ID
	void UpdateIntVector1(const UniformID& uniformID, int* value);
	void UpdateIntVector2(const UniformID& uniformID, int* value);
	void UpdateIntVector3(const UniformID& uniformID, int* value);
	void UpdateIntVector4(const UniformID& uniformID, int* value);

	//Unsigned Integers
	//Get By Name
	void UpdateUInt(const string& uniformName, unsigned int value);
	void UpdateUInt(const string& uniformName, unsigned int value1, unsigned int value2);
	void UpdateUInt(const string& uniformName, unsigned int value1, unsigned int value2, unsigned int value3);
	void UpdateUInt(const string& uniformName, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4);

	//Get By ID
	void UpdateUInt(const UniformID& uniformID, unsigned int value);
	void UpdateUInt(const UniformID& uniformID, unsigned int value1, unsigned int value2);
	void UpdateUInt(const UniformID& uniformID, unsigned int value1, unsigned int value2, unsigned int value3);
	void UpdateUInt(const UniformID& uniformID, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4);

	//Get By Name
	void UpdateUIntVector1(const string& uniformName, unsigned int* value);
	void UpdateUIntVector2(const string& uniformName, unsigned int* value);
	void UpdateUIntVector3(const string& uniformName, unsigned int* value);
	void UpdateUIntVector4(const string& uniformName, unsigned int* value);

	//Get By ID
	void UpdateUIntVector1(const UniformID& uniformID, unsigned int* value);
	void UpdateUIntVector2(const UniformID& uniformID, unsigned int* value);
	void UpdateUIntVector3(const UniformID& uniformID, unsigned int* value);
	void UpdateUIntVector4(const UniformID& uniformID, unsigned int* value);

	//Floats
	//Get By Name
	void UpdateFloat(const string& uniformName, float value);
	void UpdateFloat(const string& uniformName, float value1, float value2);
	void UpdateFloat(const string& uniformName, float value1, float value2, float value3);
	void UpdateFloat(const string& uniformName, float value1, float value2, float value3, float value4);

	//Get By ID
	void UpdateFloat(const UniformID& uniformName, float value);
	void UpdateFloat(const UniformID& uniformName, float value1, float value2);
	void UpdateFloat(const UniformID& uniformName, float value1, float value2, float value3);
	void UpdateFloat(const UniformID& uniformName, float value1, float value2, float value3, float value4);

	//Get By Name
	void UpdateFloatVector1(const string& uniformName, float* value);
	void UpdateFloatVector2(const string& uniformName, float* value);
	void UpdateFloatVector3(const string& uniformName, float* value);
	void UpdateFloatVector4(const string& uniformName, float* value);
	
	//Get By ID
	void UpdateFloatVector1(const UniformID& uniformID, float* value);
	void UpdateFloatVector2(const UniformID& uniformID, float* value);
	void UpdateFloatVector3(const UniformID& uniformID, float* value);
	void UpdateFloatVector4(const UniformID& uniformID, float* value);

	//Get By Name
	void UpdateFloatMatrix4x4(const string& uniformName, bool transpose, float* value);

	//Get By ID
	void UpdateFloatMatrix4x4(const UniformID& uniformID, bool transpose, float* value);

	//And Many More... (Not really. I'm too lazy to do the rest.)

};

#endif