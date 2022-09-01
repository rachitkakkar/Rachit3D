#pragma once
/* VERTEXARRAY CLASS: AN ABSTRACTION FOR AN OPENGL VERTEXARRAY */

#include "VertexBuffer.h"

class VertexBufferLayout; // To Avoid A Circular Include Error

class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};