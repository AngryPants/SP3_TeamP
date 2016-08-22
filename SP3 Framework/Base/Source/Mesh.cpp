#include "Mesh.h"
#include "GL\glew.h"
#include "Vertex.h"

Mesh::Mesh(const std::string &meshName) : name(meshName), mode(DRAW_TRIANGLES) {

	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
	
	textureOffset[0] = 0.0f;
	textureOffset[1] = 0.0f;
	textureScale[0] = 1.0f;
	textureScale[1] = 1.0f;

}

Mesh::~Mesh() {

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);

}

void Mesh::Render() {

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	if (mode == DRAW_LINES) {
		glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
	} else if (mode == DRAW_TRIANGLE_STRIP) {
		glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
	} else {
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glDisableVertexAttribArray(3);

}

void Mesh::Render(unsigned offset, unsigned count) {

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));

	//glDrawArrays(GL_TRIANGLES, offset, count);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	if (mode == DRAW_LINES) {
		glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
	} else if (mode == DRAW_TRIANGLE_STRIP) {
		glDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
	} else {
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

}

void Mesh::SetTextureOffset(const float& u, const float& v) {

	textureOffset[0] = u;
	textureOffset[1] = v;

	/*//Bind our mesh's vertex buffer so that we can modify it.
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//Replace the texture coordinates' data.
	for (size_t i = 0; i < vertexSize && i < texCoords.size(); ++i) {
		TexCoord texCoord(texCoords[i].u + u, texCoords[i].v + v);
		glBufferSubData(GL_ARRAY_BUFFER, (sizeof(Vertex) - sizeof(TexCoord)) + (i * sizeof(Vertex)),
		sizeof(TexCoord), &texCoord);
	}
	//Unbind our mesh.
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

}

void Mesh::GetTextureOffset(float& u, float& v) const {

	u = textureOffset[0];
	v = textureOffset[1];

}

void Mesh::SetTextureScale(const float& u, const float& v) {

	textureScale[0] = u;
	textureScale[1] = v;

	/*//Bind our mesh's vertex buffer so that we can modify it.
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//Replace the texture coordinates' data.
	for (size_t i = 0; i < vertexSize && i < texCoords.size(); ++i) {
		TexCoord texCoord(texCoords[i].u * u, texCoords[i].v * v);
		glBufferSubData(GL_ARRAY_BUFFER, (sizeof(Vertex) - sizeof(TexCoord)) + (i * sizeof(Vertex)),
		sizeof(TexCoord), &texCoord);
	}
	//Unbind our mesh.
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

}

void Mesh::GetTextureScale(float& u, float& v) const {

	u = textureScale[0];
	v = textureOffset[1];

}

//void Mesh::UpdateTexCoords() {

	////Bind our mesh's vertex buffer so that we can modify it.
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	////Replace the texture coordinates' data.
	//TexCoord texCoord;
	//for (size_t i = 0; i < vertexSize && i < texCoords.size(); ++i) {
	//	texCoord = texCoords[i];
	//	texCoord.u *= textureScaleU; //Scale
	//	texCoord.v *= textureScaleV; //Scale
	//	texCoord.u += textureOffsetU;
	//	texCoord.v += textureOffsetV;
	//	glBufferSubData(GL_ARRAY_BUFFER, (sizeof(Vertex) - sizeof(TexCoord)) + (i * sizeof(Vertex)),
	//	sizeof(TexCoord), &texCoord);
	//}
	////Unbind our mesh.
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//
	//texCoordUpdated = true;

//}