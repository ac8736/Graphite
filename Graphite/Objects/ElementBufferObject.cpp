#include "ElementBufferObject.h"
#include <iostream>

ElementBufferObject::ElementBufferObject()
{
	glGenBuffers(1, &m_Id);
}

ElementBufferObject::~ElementBufferObject()
{
	glDeleteBuffers(1, &m_Id);
}

void ElementBufferObject::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void ElementBufferObject::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBufferObject::SetIndices(GLsizeiptr size, const void* data, GLenum usage) const
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}
