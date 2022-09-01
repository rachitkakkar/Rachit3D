#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	: m_Vertices(vertices), m_Indices(indices)
{
}

Mesh::~Mesh()
{
}