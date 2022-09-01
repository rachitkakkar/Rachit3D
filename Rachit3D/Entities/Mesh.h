#pragma once
/* VERTEX STRUCT: HOLDS A POSITION, NORMAL, COLOR, AND TEXTURE COORDINATE */
/* MESH CLASS: HOLDS THE REQUIRED COMPONENTS TO DRAW A MESH */

#include "../Renderer/Texture.h"

#include <vector>

#include <glm/glm.hpp>

struct Vertex
{
public:
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Color;
	glm::vec2 TexCoord;
};

class Mesh
{
private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();

	inline Vertex* GetVertices() { return m_Vertices.data(); }
	inline unsigned int GetSizeOfVertices() { return (m_Vertices.size() * sizeof(Vertex)); }

	inline unsigned int* GetIndices() { return m_Indices.data(); }
	inline unsigned int GetSizeOfIndices() { return (m_Indices.size() * sizeof(unsigned int)); }
};