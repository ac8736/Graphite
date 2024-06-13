#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject()
{
	glGenBuffers(1, &m_Id);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &m_Id);
}

void VertexBufferObject::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void VertexBufferObject::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::SetData(GLsizeiptr size, const void* data, unsigned int drawMode) const
{
	glBufferData(GL_ARRAY_BUFFER, size, data, drawMode);
}
