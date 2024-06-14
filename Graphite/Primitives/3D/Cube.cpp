#include "Cube.h"

Cube::Cube(bool includeTextures, bool includeNormals) : m_ModelMatrix(glm::mat4(1.0f))
{
	m_VAO.Bind();
	m_VBO.Bind();
	m_VBO.SetData(sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

	m_VAO.SetVertexAttrib(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	if (includeTextures)
	{
		m_VAO.SetVertexAttrib(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	if (includeNormals)
	{
		m_VAO.SetVertexAttrib(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	}

	m_EBO.Bind();
	m_EBO.SetIndices(sizeof(m_Indices), m_Indices, GL_STATIC_DRAW);
	m_VAO.Unbind();
	m_VBO.Unbind();
	m_EBO.Unbind();
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

void Cube::ResetPosition()
{
	// Extract the scaling components
	glm::vec3 scale{};
	scale.x = glm::length(glm::vec3(m_ModelMatrix[0])); // Length of the first column vector
	scale.y = glm::length(glm::vec3(m_ModelMatrix[1])); // Length of the second column vector
	scale.z = glm::length(glm::vec3(m_ModelMatrix[2])); // Length of the third column vector

	// Normalize the columns to remove the scaling
	m_ModelMatrix[0] = glm::normalize(m_ModelMatrix[0]);
	m_ModelMatrix[1] = glm::normalize(m_ModelMatrix[1]);
	m_ModelMatrix[2] = glm::normalize(m_ModelMatrix[2]);

	// Reset the translation components
	m_ModelMatrix[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	// Reapply the scaling
	m_ModelMatrix[0] *= scale.x;
	m_ModelMatrix[1] *= scale.y;
	m_ModelMatrix[2] *= scale.z;
}

void Cube::Translate(glm::vec3 translation)
{
	m_ModelMatrix = glm::translate(m_ModelMatrix, translation);
}

void Cube::Rotate(float angle)
{
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Cube::Scale(glm::vec3 scale)
{
	m_ModelMatrix = glm::scale(m_ModelMatrix, scale);
}

void Cube::Draw(Shader& shader) const
{
	Bind();
	shader.SetUniformMatrix4fv("model", m_ModelMatrix);
	glDrawElements(GL_TRIANGLES, GetIndicesCount(), GL_UNSIGNED_INT, 0);
	Unbind();
}
