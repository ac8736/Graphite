#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>

#include "Objects/VertexArrayObject.h"
#include "Objects/VertexBufferObject.h"
#include "Objects/ElementBufferObject.h"
#include <Shaders/Shader.h>

class Pyramid
{
public:
	Pyramid();
	~Pyramid();

	void Bind() const;
	void Unbind() const;

	void Translate(glm::vec3 translate);
	void Rotate(float angle);
	void Scale(glm::vec3 scale);

	inline const glm::mat4 GetModelMatrix() const { return m_ModelMatrix; }
	inline const unsigned int GetIndicesCount() const { return sizeof(m_Indices) / sizeof(unsigned int); }

	void Draw(Shader& shader) const;

private:
	VertexArrayObject m_VAO;
	VertexBufferObject m_VBO;
	ElementBufferObject m_EBO;

	glm::mat4 m_ModelMatrix;

	float m_Vertices[25] = {
		// Base
		-0.5f, 0.0f, -0.5f, 0.0f, 0.0f, // Bottom left (0)
		 0.5f, 0.0f, -0.5f, 1.0f, 0.0f, // Bottom right (1)
		 0.5f, 0.0f,  0.5f, 1.0f, 1.0f, // Top right (2)
		-0.5f, 0.0f,  0.5f, 0.0f, 1.0f, // Top left (3)
		// Apex
		 0.0f, 1.0f,  0.0f, 0.5f, 0.5f  // Top (4)
	};
	unsigned int m_Indices[18] = {
		// Base
		0, 1, 2,
		2, 3, 0,
		// Sides
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};
};
