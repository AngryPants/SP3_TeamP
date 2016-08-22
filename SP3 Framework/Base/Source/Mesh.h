#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "Material.h"
#include "Vertex.h"

using std::string;
using std::vector;

struct Mesh {

public:
	//Enum(s)
	enum DRAW_MODE {
		DRAW_TRIANGLES, //Default Mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};

	//Variable(s)
	const std::string name;
	DRAW_MODE mode;
	//vector<TexCoord> texCoords;
	unsigned int vertexBuffer;
	unsigned int vertexSize; //Number of vertices.
	unsigned int indexBuffer;
	unsigned int indexSize;
	Material material;

	//Texture Coordinates
	float textureOffset[2]; //0 = u, 1 = v
	float textureScale[2]; //0 = u, 1 = v

	//Constructor(s) & Destructor
	Mesh(const std::string &meshName);
	virtual ~Mesh();

	void SetTextureOffset(const float& u, const float& v);
	void GetTextureOffset(float& u, float& v) const;
	void SetTextureScale(const float& u, const float& v);
	void GetTextureScale(float& u, float& v) const;

	//Function(s)
	virtual void Render();
	virtual void Render(unsigned offset, unsigned count);

};

#endif