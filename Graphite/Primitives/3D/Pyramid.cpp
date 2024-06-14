#include "Pyramid.h"

Pyramid::Pyramid() : m_ModelMatrix(glm::mat4(1.0f))
{
	m_VAO.Bind();
	m_VBO.Bind();
	m_VBO.SetData(sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

	m_VAO.SetVertexAttrib(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	m_VAO.SetVertexAttrib(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	m_EBO.Bind();
	m_EBO.SetIndices(sizeof(m_Indices), m_Indices, GL_STATIC_DRAW);
	m_VAO.Unbind();
	m_VBO.Unbind();
	m_EBO.Unbind();
}

Pyramid::~Pyramid()
{
}

void Pyramid::Bind() const
{
	m_VAO.Bind();
}

void Pyramid::Unbind() const
{
	m_VAO.Unbind();
}

void Pyramid::Translate(glm::vec3 translation)
{
	m_ModelMatrix = glm::translate(m_ModelMatrix, translation);
}

void Pyramid::Rotate(float angle)
{
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Pyramid::Scale(glm::vec3 scale)
{
	m_ModelMatrix = glm::scale(m_ModelMatrix, scale);
}

void Pyramid::Draw(Shader& shader) const
{
	Bind();
	shader.SetUniformMatrix4fv("model", m_ModelMatrix);
	glDrawElements(GL_TRIANGLES, GetIndicesCount(), GL_UNSIGNED_INT, 0);
	Unbind();
}
