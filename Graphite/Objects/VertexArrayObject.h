#pragma once
#include "glad/glad.h"

class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();

	void Bind() const;
	void Unbind() const;

	void SetVertexAttrib(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void* pointer);
private:
	unsigned int m_Id;

};