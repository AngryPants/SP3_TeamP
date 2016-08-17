#include <vector>
#include <GL\glew.h>
#include "Vertex.h"
#include "MyMath.h"
#include "LoadOBJ.h"
#include "LoadHmap.h"
#include <iostream>
#include "MeshBuilder.h"

using namespace std;

bool MeshBuilder::CheckMeshExist(const string& meshName) const {

	return meshMap.count(meshName) != 0;

}

bool MeshBuilder::CheckSpriteAnimationExist(const string& spriteName) const {

	return spriteMap.count(spriteName) != 0;

}

Mesh* MeshBuilder::GetMesh(const string& meshName) {

	MeshMap::iterator mapIter = meshMap.find(meshName);
	if (mapIter != meshMap.end()) {
		return mapIter->second;
	}

	return nullptr;

}

SpriteAnimation* MeshBuilder::GetSpriteAnimation(const string& spriteName) {

	SpriteMap::iterator mapIter = spriteMap.find(spriteName);
	if (mapIter != spriteMap.end()) {
		return mapIter->second;
	}

	return nullptr;

}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float length) {

	Mesh* mesh = GetMesh(meshName);
	if (mesh != nullptr) {
		return mesh;
	}

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	
	Vertex v;
	v.color.Set(color.r, color.g, color.b);
	v.normal.Set(0, 0, 1);

	v.pos.Set(-0.5f * length, 0.5f * length, 0);
	v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, -0.5f * length, 0);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	
	v.pos.Set(0.5f * length, 0.5f * length, 0);
	v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, -0.5f * length, 0);
	v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);
	
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	
	mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind the EBO

	mesh->vertexSize = vertex_buffer_data.size();
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	//TexCoords
	for (size_t i = 0; i < vertex_buffer_data.size(); ++i) {
		mesh->texCoords.push_back(vertex_buffer_data[i].texCoord);
	}

	meshMap.insert(pair<string, Mesh*>(meshName, mesh));

	return mesh;

}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float length) {

	Mesh* mesh = GetMesh(meshName);
	if (mesh != nullptr) {
		return mesh;
	}

	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;

	Vertex v;
	v.color = color;

	//Front
	v.normal.Set(0.0f, 0.0f, 1.0f);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);

	//Left
	v.normal.Set(1.0f, 0.0f, 0.0f);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);

	//Back
	v.normal.Set(0.0f, 0.0f, -1.0f);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);

	//Right
	v.normal.Set(-1.0f, 0.0f, 0.0f);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);

	//Up
	v.normal.Set(0.0f, 1.0f, 0.0f);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);

	//Down
	v.normal.Set(0.0f, -1.0f, 0.0f);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);
	vertex_buffer_data.push_back(v);

	for (unsigned int i = 0; i < 6; ++i) {
		index_buffer_data.push_back(0 + i * 4);
		index_buffer_data.push_back(1 + i * 4);
		index_buffer_data.push_back(2 + i * 4);
		index_buffer_data.push_back(0 + i * 4);
		index_buffer_data.push_back(2 + i * 4);
		index_buffer_data.push_back(3 + i * 4);
	}

	mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind the EBO

	mesh->vertexSize = vertex_buffer_data.size();
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	//TexCoords
	for (size_t i = 0; i < vertex_buffer_data.size(); ++i) {
		mesh->texCoords.push_back(vertex_buffer_data[i].texCoord);
	}

	meshMap.insert(pair<string, Mesh*>(meshName, mesh));

	return mesh;

}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, unsigned numSlice, float outerR, float innerR) {

	Mesh* mesh = GetMesh(meshName);
	if (mesh != nullptr) {
		return mesh;
	}

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;
	v.normal.Set(0, 0, 1);

	float degreePerSlice = 360.f / numSlice;
	for(unsigned int slice = 0; slice < numSlice + 1; ++slice) {
		float theta = slice * degreePerSlice;
		
		v.pos.Set(outerR * cos(Math::DegreeToRadian(theta)), outerR * sin(Math::DegreeToRadian(theta)), 0);
		vertex_buffer_data.push_back(v);
		
		v.pos.Set(innerR * cos(Math::DegreeToRadian(theta)), innerR * sin(Math::DegreeToRadian(theta)), 0);
		vertex_buffer_data.push_back(v);
	}
	for(unsigned int slice = 0; slice < numSlice + 1; ++slice) {
		index_buffer_data.push_back(2 * slice + 0);
		index_buffer_data.push_back(2 * slice + 1);
	}

	mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind the EBO

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->vertexSize = vertex_buffer_data.size();
	mesh->indexSize = index_buffer_data.size();
	//TexCoords
	for (size_t i = 0; i < vertex_buffer_data.size(); ++i) {
		mesh->texCoords.push_back(vertex_buffer_data[i].texCoord);
	}

	meshMap.insert(pair<string, Mesh*>(meshName, mesh));

	return mesh;

}

float sphereX(float phi, float theta) {

	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));

}
float sphereY(float phi, float theta) {

	return sin(Math::DegreeToRadian(phi));

}

float sphereZ(float phi, float theta) {

	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));

}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius) {

	Mesh* mesh = GetMesh(meshName);
	if (mesh != nullptr) {
		return mesh;
	}

	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	
	float degreePerStack = 180.f / numStack;
	float degreePerSlice = 360.f / numSlice;

	for (unsigned stack = 0; stack < numStack + 1; ++stack) { //stack //replace with 180 for sphere
		float phi = -90.f + stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) { //slice
			float theta = slice * degreePerSlice;
			Vertex v;
			v.pos.Set(radius * sphereX(phi, theta), radius * sphereY(phi, theta), radius * sphereZ(phi, theta));
			v.color = color;
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStack; ++stack) {
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) {
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	mesh = new Mesh(meshName);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind the EBO

	mesh->vertexSize = vertex_buffer_data.size();
	mesh->indexSize = index_buffer_data.size();
	//TexCoords
	for (size_t i = 0; i < vertex_buffer_data.size(); ++i) {
		mesh->texCoords.push_back(vertex_buffer_data[i].texCoord);
	}

	meshMap.insert(pair<string, Mesh*>(meshName, mesh));

	return mesh;

}

Mesh* MeshBuilder::GenerateSkyPlane(const std::string &meshName, Color color, unsigned int numSlices, float planetRadius, float atmosphereRadius, float uTile, float vTile) {

	Mesh* mesh = GetMesh(meshName);
	if (mesh != nullptr) {
		return mesh;
	}

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	if (numSlices < 1) {
		numSlices = 1;
	} else if (numSlices > 1024) {
		numSlices = 1024;
	}
	if (planetRadius < 1.0f) {
		planetRadius = 1.0f;
	}
	if (atmosphereRadius < 1.0f) {
		atmosphereRadius = 1.0f;
	}

	//Calculate some values that are necessary for plane size.
	float planeSize = planetRadius * 2.0f;
	float delta = planeSize / (float)numSlices; //Length of each small square.
	float texDelta = 2.0f / (float)numSlices;

	for (unsigned int z = 0; z <= numSlices; ++z) {
		for (unsigned int x = 0; x <= numSlices; ++x) {
			float xDist = (-0.5f * planeSize) + ((float)x * delta);
			float zDist = (-0.5f * planeSize) + ((float)z * delta);

			float xHeight = ((xDist * xDist) / (0.5 * planeSize * 0.5 * planeSize)) * atmosphereRadius; //y = x * x parabola graph
			float zHeight = ((zDist * zDist) / (0.5 * planeSize * 0.5 * planeSize)) * atmosphereRadius; //y = x * x parabola graph

			float height = xHeight + zHeight;

			Vertex v;
			v.color = color;
			v.pos.Set(xDist, atmosphereRadius - height, zDist);
			v.texCoord.u = uTile * ((float)x * texDelta * 0.5f);
			v.texCoord.v = vTile * (1.0f - ((float) z * texDelta * 0.5f));
			vertex_buffer_data.push_back(v);
		}
	}

	//Calculate the indices
	int index = 0;
	
	for (int i = 0; i < numSlices; ++i) {
		for (int j = 0; j < numSlices; ++j) {
			int startvert = (i * (numSlices + 1) + j);
			index_buffer_data.push_back(startvert); //Triangle 1
			index_buffer_data.push_back(startvert + 1);
			index_buffer_data.push_back(startvert + numSlices + 1);

			index_buffer_data.push_back(startvert + 1); //Triangle 2
			index_buffer_data.push_back(startvert + numSlices + 2);
			index_buffer_data.push_back(startvert + numSlices + 1);
		}
	}

	mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind the EBO

	mesh->vertexSize = vertex_buffer_data.size();
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	//TexCoords
	for (size_t i = 0; i < vertex_buffer_data.size(); ++i) {
		mesh->texCoords.push_back(vertex_buffer_data[i].texCoord);
	}

	meshMap.insert(pair<string, Mesh*>(meshName, mesh));

	return mesh;

}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string& filePath) {

	Mesh* mesh = GetMesh(meshName);
	if (mesh != nullptr) {
		return mesh;
	}

	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(filePath.c_str(), vertices, uvs, normals);
	if(!success) {
		return nullptr;
	}

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);

	mesh = new Mesh(meshName);
	
	mesh->mode = Mesh::DRAW_TRIANGLES;
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind the EBO

	mesh->vertexSize = vertex_buffer_data.size();
	mesh->indexSize = index_buffer_data.size();
	//TexCoords
	for (size_t i = 0; i < vertex_buffer_data.size(); ++i) {
		mesh->texCoords.push_back(vertex_buffer_data[i].texCoord);
	}

	meshMap.insert(pair<string, Mesh*>(meshName, mesh));

	return mesh;

}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol) {

	Mesh* mesh = GetMesh(meshName);
	if (mesh != nullptr) {
		return mesh;
	}

	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	
	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;
	for(unsigned i = 0; i < numRow; ++i)
	{
		for(unsigned j = 0; j < numCol; ++j)
		{
			float u1 = j * width;
			float v1 = 1.f - height - i * height;
			v.pos.Set(-0.5f, -0.5f, 0);
			v.texCoord.Set(u1, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, -0.5f, 0);
			v.texCoord.Set(u1 + width, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, 0.5f, 0);
			v.texCoord.Set(u1 + width, v1 + height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.5f, 0);
			v.texCoord.Set(u1, v1 + height);
			vertex_buffer_data.push_back(v);
	
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}
	
	mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind the EBO

	mesh->vertexSize = vertex_buffer_data.size();
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	//TexCoords
	for (size_t i = 0; i < vertex_buffer_data.size(); ++i) {
		mesh->texCoords.push_back(vertex_buffer_data[i].texCoord);
	}

	meshMap.insert(pair<string, Mesh*>(meshName, mesh));

	return mesh;

}

Vector3 CalculateTerrainNormal(float heightLeft, float heightRight, float heightUp, float heightDown) {

	//	0--------------------------->X
	//	|
	//	|			Up
	//	|			|
	//	|	 Left - P - Right
	//	|			|
	//	|	   	   Down
	//	|
	//	v
	//	Z

	return Vector3(heightLeft - heightRight, 2.0f, heightUp - heightDown).Normalize();

}

Mesh* MeshBuilder::GenerateTerrain(const std::string &meshName, const std::string filePath, std::vector<unsigned char> &heightMap, unsigned int uTile, unsigned int vTile) {

	Mesh* mesh = GetMesh(meshName);
	if (mesh != nullptr) {
		return mesh;
	}

	if (!LoadHeightMap(filePath.c_str(), heightMap)) {
		return nullptr;
	}

	Vertex v;
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;

	if (uTile < 1) {
		uTile = 1;
	}
	if (vTile < 1) {
		vTile;
	}

	float scaleFactor = 256.0f; //256 is because we are saving the .raw as an 8bit greyscale image. Hence 8bit = 256.
	v.normal.Set(0, 1, 0); //Give it a default value;
	unsigned int terrainSize = (unsigned int)sqrt((double)heightMap.size());
	for (unsigned int z = 0; z < terrainSize; ++z) {
		for (unsigned int x = 0; x < terrainSize; ++x) {
			float scaledHeight = (float)heightMap[z * terrainSize + x] / scaleFactor;

			v.pos.Set(static_cast<float>(x) / terrainSize - 0.5f, scaledHeight, static_cast<float>(z) / terrainSize - 0.5f); //Right now the coords are starting from 0 to 1. We -0.5f to make it start from -0.5 to 0.5.
			v.color.Set(scaledHeight, scaledHeight, scaledHeight); //Rendering heighmap without texture.
			v.texCoord.Set(1.0f - (float)x / terrainSize * uTile, (float)z / terrainSize * vTile);

			if (z > 1 && z < terrainSize - 1 && x > 1 && x < terrainSize - 1) {
				float hL = heightMap[z * terrainSize + x - 1] / scaleFactor;
				float hR = heightMap[z * terrainSize + x + 1] / scaleFactor;
				float hU = heightMap[(z - 1) * terrainSize + x] / scaleFactor;
				float hD = heightMap[(z + 1) * terrainSize + x] / scaleFactor;
				v.normal = CalculateTerrainNormal(hL, hR, hU, hD);
			}

			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned int z = 0; z < terrainSize - 1; ++z) {
		for (unsigned int x = 0; x < terrainSize - 1; ++x) {
			//Triangle 1
			index_buffer_data.push_back(terrainSize * z + x);
			index_buffer_data.push_back(terrainSize * (z + 1) + x);
			index_buffer_data.push_back(terrainSize * z + x + 1);

			//Triangle 2
			index_buffer_data.push_back(terrainSize * (z + 1) + x + 1);
			index_buffer_data.push_back(terrainSize * z + x + 1);
			index_buffer_data.push_back(terrainSize* (z + 1) + x);
		}
	}
	
	mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind the EBO

	mesh->vertexSize = vertex_buffer_data.size();
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	//TexCoords
	for (size_t i = 0; i < vertex_buffer_data.size(); ++i) {
		mesh->texCoords.push_back(vertex_buffer_data[i].texCoord);
	}

	meshMap.insert(pair<string, Mesh*>(meshName, mesh));

	return mesh;

}

SpriteAnimation* MeshBuilder::GenerateSpriteAnimation(const string& meshName, unsigned int numRow, unsigned int numColumn) {

	SpriteAnimation* mesh = GetSpriteAnimation(meshName);
	if (mesh != nullptr) {
		return mesh;
	}

	if (numRow < 1) {
		numRow = 1;
	}
	if (numColumn < 1) {
		numColumn = 1;
	}

	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	
	float width = 1.f / numColumn;
	float height = 1.f / numRow;
	int offset = 0;

	Vertex v;
	v.normal.Set(0, 0, 1);
	for (unsigned i = 0; i < numRow; ++i) {
		for (unsigned j = 0; j < numColumn; ++j) {
			float u1 = j * width;
			float v1 = 1.f - height - i * height;
			v.pos.Set(-0.5f, -0.5f, 0);
			v.texCoord.Set(u1, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, -0.5f, 0);
			v.texCoord.Set(u1 + width, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, 0.5f, 0);
			v.texCoord.Set(u1 + width, v1 + height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.5f, 0);
			v.texCoord.Set(u1, v1 + height);
			vertex_buffer_data.push_back(v);
	
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}

	mesh = new SpriteAnimation(meshName, numRow, numColumn);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Unbind the EBO

	mesh->vertexSize = vertex_buffer_data.size();
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	//TexCoords
	for (size_t i = 0; i < vertex_buffer_data.size(); ++i) {
		mesh->texCoords.push_back(vertex_buffer_data[i].texCoord);
	}

	spriteMap.insert(pair<string, SpriteAnimation*>(meshName, mesh));

	return mesh;

}