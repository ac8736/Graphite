#pragma once
#include <glad/glad.h>

class ElementBufferObject
{
public:
	ElementBufferObject();
	~ElementBufferObject();

	void Bind() const;
	void Unbind() const;

	void SetIndices(GLsizeiptr size, const void* data, GLenum usage) const;

private:
	unsigned int m_Id;
};
