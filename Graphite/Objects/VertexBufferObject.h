#pragma once
#include <glad/glad.h>

class VertexBufferObject
{
public:
	VertexBufferObject();
	~VertexBufferObject();

	void Bind() const;
	void Unbind() const;

	void SetData(GLsizeiptr size, const void* data, unsigned int drawMode) const;

private:
	unsigned int m_Id;
};