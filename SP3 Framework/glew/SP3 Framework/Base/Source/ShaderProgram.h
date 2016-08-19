#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <vector>
#include <string>

using std::string;

typedef unsigned int ProgramID;
typedef unsigned int UniformID;
typedef std::vector<UniformID> UniformVec;

/******************************************************************************/
/*!
\brief
A general class used to manage OpenGL's shaders including their creation and
configuration.

In rendering, shaders are pieces of code that defines how an object is
rendered. In the OpenGL pipeline, you are allowed to configure 2 steps in the
rendering of polygons with two shaders; the vertex shader and the fragment
shader. The vertex shader configures the position of the vertex and passes on
the information to the fragment shader which will configure the coloring of the
polygon. The shaderProgram manages both at once. Be sure to initialise OpenGL
before use. It WILL crash otherwise. Also, most operating systems use different
OpenGL context for different windows. Switch windows and you switch context
(which also means switching shaders too!) Keep that in mind when you are
switching windows and suddenly the shader you are using does not exist anymore
or if you are using a different shader entirely.

*/
/******************************************************************************/
class ShaderProgram {

private:
	/******************************************************************************/
	/*!
	\brief
	The id of the shader program that OpenGL will use to identify different shader
	programs in the same context.

	*/
	/******************************************************************************/
	ProgramID programID;
	/******************************************************************************/
	/*!
	\brief
	A vector of ids for the different uniforms in the shader.

	Uniforms are variables in the shader that will exist throughout the shader's
	lifespan. They are a way for the CPU to vary the rendering of different objects
	by changing the uniforms like transparency, color etc. Note that the vector
	includes ids of uniforms from both shaders.

	*/
	/******************************************************************************/
	UniformVec uniformID;
	/******************************************************************************/
	/*!
	\brief
	The address of the two shaders.

	Shaders in OpenGL are defined through files with text. These files contain the
	code for the shader and OpenGL loads both of them in at shader initialisation.

	*/
	/******************************************************************************/
	string vertexShader, fragmentShader;

public:
	template<std::size_t size, class Type>
	struct Vector {
		Type vec[size];	
	};

	template<std::size_t rows, std::size_t column, class Type>
	struct Matrix {
		Type mat[rows * column];	
	};

	using IntVec2 = Vector<2, int>;
	using UIntVec2 = Vector<2, unsigned int>;
	using FloatVec2 = Vector<2, float>;
	using DoubleVec2 = Vector<2, double>;
	using IntVec3 = Vector<3, int>;
	using UIntVec3 = Vector<3, unsigned int>;
	using FloatVec3 = Vector<3, float>;
	using DoubleVec3 = Vector<3, double>;
	using IntVec4 = Vector<4, int>;
	using UIntVec4 = Vector<4, unsigned int>;
	using FloatVec4 = Vector<4, float>;
	using DoubleVec4 = Vector<4, double>;

	using FloatMat4x4 = Matrix<4, 4, float>;
	using DoubleMat4x4 = Matrix<4, 4, double>;

	/******************************************************************************/
	/*!
	\brief
	The name of the shader.

	*/
	/******************************************************************************/
	const string name;

	/******************************************************************************/
	/*!
	\brief
	Constructor

	\param name
	The name of the shader.

	*/
	/******************************************************************************/
	ShaderProgram(const string& name);
	/******************************************************************************/
	/*!
	\brief
	Virtual destructor.

	*/
	/******************************************************************************/
	virtual ~ShaderProgram();

	//Vertex Shader & Fragment Shader File
	/******************************************************************************/
	/*!
	\brief
	Return the address of the vertex shader file.

	\return
	The address of the vertex shader file.

	*/
	/******************************************************************************/
	string GetVertexShaderFile() const;
	/******************************************************************************/
	/*!
	\brief
	Return the address of the fragment shader file.

	\return
	The address of the fragment shader file.

	*/
	/******************************************************************************/
	string GetFragmentShaderFile() const;

	/******************************************************************************/
	/*!
	\brief
	Set the ShaderProgram with the two shader files.

	\param vertexShader
	The address of the vertex shader file.

	\param fragmentShader
	The address of the fragmentShader file.

	\return
	True if successful. False if otherwise.

	*/
	/******************************************************************************/
	bool SetShader(const string& vertexShader, const string& fragmentShader);
	/******************************************************************************/
	/*!
	\brief
	Delete the shader program from OpenGL.

	\return
	True if successful. False if otherwise.

	*/
	/******************************************************************************/
	bool DeleteShader();
	/******************************************************************************/
	/*!
	\brief
	Return the program id of the shader program in OpenGL.

	\return
	The program id.

	*/
	/******************************************************************************/
	ProgramID GetProgramID();
	/******************************************************************************/
	/*!
	\brief
	Return the id of the uniform in the shaders.

	\param uniformName
	The name of the uniform in the shaders.

	\return
	The id of the uniform.

	*/
	/******************************************************************************/
	UniformID GetUniformID(const string& uniformName);

	//Textures
	/******************************************************************************/
	/*!
	\brief
	Sets the active texture for rendering.

	\param index
	The index of the texture.

	\return
	True if successful. False if otherwise.

	*/
	/******************************************************************************/
	bool SetActiveTexture(const unsigned int index);
	/******************************************************************************/
	/*!
	\brief
	Bind to a certain texture to change it.

	\param textureID
	The index of the texture.

	\return
	True if successful. False if otherwise.

	*/
	/******************************************************************************/
	bool BindTexture(const unsigned int textureID);
	/******************************************************************************/
	/*!
	\brief
	Unbinds the currently binded texture to prevent any more changes to it.

	\return
	True if successful. False if otherwise.

	*/
	/******************************************************************************/
	bool UnbindTexture();

	//Updating Uniforms (Wow, this is gonna be long...)
	
	//Boolean
	void Update(const UniformID uniformID, const bool value);

	//Integers
	void Update(const UniformID uniformID, const int value);
	void Update(const UniformID uniformID, const int value1, const int value2);
	void Update(const UniformID uniformID, const int value1, const int value2, const int value3);
	void Update(const UniformID uniformID, const int value1, const int value2, const int value3, const int value4);

	void Update(const UniformID uniformID, const IntVec2& value);
	void Update(const UniformID uniformID, const IntVec3& value);
	void Update(const UniformID uniformID, const IntVec4& value);

	void Update(const UniformID uniformID, const int* value, const unsigned number);
	void Update(const UniformID uniformID, const IntVec2& value, const unsigned number);
	void Update(const UniformID uniformID, const IntVec3& value, const unsigned number);
	void Update(const UniformID uniformID, const IntVec4& value, const unsigned number);

	//Unsigned Integers
	void Update(const UniformID uniformID, const unsigned int value);
	void Update(const UniformID uniformID, const unsigned int value1, const unsigned int value2);
	void Update(const UniformID uniformID, const unsigned int value1, const unsigned int value2, const unsigned int value3);
	void Update(const UniformID uniformID, const unsigned int value1, const unsigned int value2, const unsigned int value3, const unsigned int value4);

	void Update(const UniformID uniformID, const UIntVec2& value);
	void Update(const UniformID uniformID, const UIntVec3& value);
	void Update(const UniformID uniformID, const UIntVec4& value);

	void Update(const UniformID uniformID, const unsigned int* value, const unsigned number);
	void Update(const UniformID uniformID, const UIntVec2& value, const unsigned number);
	void Update(const UniformID uniformID, const UIntVec3& value, const unsigned number);
	void Update(const UniformID uniformID, const UIntVec4& value, const unsigned number);

	//Floats
	void Update(const UniformID uniformID, const float value);
	void Update(const UniformID uniformID, const float value1, const float value2);
	void Update(const UniformID uniformID, const float value1, const float value2, const float value3);
	void Update(const UniformID uniformID, const float value1, const float value2, const float value3, const float value4);

	void Update(const UniformID uniformID, const FloatVec2& value);
	void Update(const UniformID uniformID, const FloatVec3& value);
	void Update(const UniformID uniformID, const FloatVec4& value);

	void Update(const UniformID uniformID, const float* value, const unsigned number);
	void Update(const UniformID uniformID, const FloatVec2& value, const unsigned number);
	void Update(const UniformID uniformID, const FloatVec3& value, const unsigned number);
	void Update(const UniformID uniformID, const FloatVec4& value, const unsigned number);

	void Update(const UniformID uniformID, const bool transpose, const FloatMat4x4& value);

	void Update(const UniformID uniformID, const bool transpose, const FloatMat4x4& value, const unsigned number);

	//Doubles
	void Update(const UniformID uniformID, const double value);
	void Update(const UniformID uniformID, const double value1, const double value2);
	void Update(const UniformID uniformID, const double value1, const double value2, const double value3);
	void Update(const UniformID uniformID, const double value1, const double value2, const double value3, const double value4);

	void Update(const UniformID uniformID, const DoubleVec2& value);
	void Update(const UniformID uniformID, const DoubleVec3& value);
	void Update(const UniformID uniformID, const DoubleVec4& value);

	void Update(const UniformID uniformID, const double* value, const unsigned number);
	void Update(const UniformID uniformID, const DoubleVec2& value, const unsigned number);
	void Update(const UniformID uniformID, const DoubleVec3& value, const unsigned number);
	void Update(const UniformID uniformID, const DoubleVec4& value, const unsigned number);

	void Update(const UniformID uniformID, const bool transpose, const DoubleMat4x4& value);

	void Update(const UniformID uniformID, const bool transpose, const DoubleMat4x4& value, const unsigned number);

	//And Many More... (Not really. I'm too lazy to do the rest.)

};

#endif