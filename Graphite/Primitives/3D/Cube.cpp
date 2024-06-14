#include "Cube.h"

Cube::Cube() : m_ModelMatrix(glm::mat4(1.0f))
{
	m_VAO.Bind();
	m_VBO.Bind();
	m_VBO.SetData(sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

	m_VAO.SetVertexAttrib(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	m_VAO.SetVertexAttrib(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	m_EBO.Bind();
	m_EBO.SetIndices(sizeof(m_Indices), m_Indices, GL_STATIC_DRAW);
	m_VAO.Unbind();
}

Cube::~Cube()
{
}

void Cube::Bind() const
{
	m_VAO.Bind();
}

void Cube::Unbind() const
{
	m_VAO.Unbind();
}

glm::mat4 Cube::GetModelMatrix() const
{
	return m_ModelMatrix;
}

unsigned int Cube::GetIndicesCount() const
{
	return sizeof(m_Indices) / sizeof(float);
}

void Cube::Translate(glm::vec3 translation)
{
	m_ModelMatrix = glm::translate(m_ModelMatrix, translation);
}

void Cube::Rotate(float angle)
{
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}
