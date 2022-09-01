#pragma once
/* VERTEXBUFFER CLASS: AN ABSTRACTION FOR AN OPENGL VERTEXBUFFER */

class VertexBuffer
{
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};