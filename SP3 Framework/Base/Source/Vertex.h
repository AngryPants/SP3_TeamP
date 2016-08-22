#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"

struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) {Set(x, y, z);}
	void Set(float x, float y, float z) {this->x = x; this->y = y; this->z = z;}
};

struct Color
{
	float r, g, b;
	Color(float r = 1, float g = 1, float b = 1) {Set(r, g, b);}
	void Set(float r, float g, float b) {this->r = r; this->g = g; this->b = b;}
};

struct TexCoord
{
	float u, v;
	TexCoord(const float& u = 0, const float& v = 0) {Set(u, v);}
	TexCoord(const TexCoord& rhs) {Set(rhs.u, rhs.v);}
	void Set(const float& u, const float& v) {this->u = u; this->v = v;}
	TexCoord& operator=(const TexCoord& rhs) {this->u = rhs.u; this->v = rhs.v; return *this;}
};

struct Vertex 
{
	Position pos;
	Color color;
	Vector3 normal;
	TexCoord texCoord;
	Vertex(){}
	~Vertex(){}
};

#endif