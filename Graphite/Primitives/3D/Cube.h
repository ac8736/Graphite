#pragma once
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "Objects/VertexArrayObject.h"
#include "Objects/VertexBufferObject.h"
#include "Objects/ElementBufferObject.h"

class Cube
{
public:
	Cube();
    ~Cube();

    void Bind() const;
    void Unbind() const;

    inline const glm::mat4 GetModelMatrix() const { return m_ModelMatrix; }
    inline const unsigned int GetIndicesCount() const { return sizeof(m_Indices) / sizeof(float); }

    void Translate(glm::vec3 translate);
    void Rotate(float angle);
    void Scale(glm::vec3 scale);

private:
    VertexArrayObject m_VAO;
    VertexBufferObject m_VBO;
    ElementBufferObject m_EBO;

    glm::mat4 m_ModelMatrix;

    float m_Vertices[120] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    };
    unsigned int m_Indices[36] = {
        0, 1, 3,    // face 1
        1, 2, 3,

        4, 5, 7,    // face 2
        5, 6, 7,

        8, 9, 11,   // face 3
        9, 10, 11,

        12, 13, 15, // face 4
        13, 14, 15,

        16, 17, 19, // face 5
        17, 18, 19,

        20, 21, 23, // face 6
        21, 22, 23
    };

};
