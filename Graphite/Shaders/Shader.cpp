#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"

Shader::Shader(const ShaderSource& shaderSource)
{
	std::string vertexShaderSource = shaderSource.VertexSource;
	std::string fragmentShaderSource = shaderSource.FragmentSource;

	unsigned int vertexId = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentId = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	m_Id = glCreateProgram();
	glAttachShader(m_Id, vertexId);
	glAttachShader(m_Id, fragmentId);
	glLinkProgram(m_Id);

	int success;
	char infoLog[512];
	glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_Id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

Shader::~Shader()
{
	glDeleteProgram(m_Id);
}

void Shader::Bind() const 
{
	glUseProgram(m_Id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform3f(const std::string& name, const glm::vec3& value) const
{
	unsigned int location = glGetUniformLocation(m_Id, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetUniform4f(const std::string& name, const glm::vec4& value) const
{
	unsigned int location = glGetUniformLocation(m_Id, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetUniform1i(const std::string& name, int value) const
{
	unsigned int location = glGetUniformLocation(m_Id, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetUniformMatrix4fv(const std::string& name, const glm::mat4& value) const
{
	unsigned int location = glGetUniformLocation(m_Id, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& shaderSource)
{
	const char* shader = shaderSource.c_str();
	unsigned int id = glCreateShader(type);

	glShaderSource(id, 1, &shader, NULL);
	glCompileShader(id);

	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return id;
}

ShaderSource Shader::ParseShaders(const std::string& vertexPath, const std::string& fragmentPath)
{
	enum ShaderType
	{
		None = -1, Vertex = 0, Fragment = 1
	};

	std::stringstream ss[2];

	std::ifstream vertexShader(vertexPath);
	if (vertexShader.is_open())
	{
		std::string line;
		while (std::getline(vertexShader, line))
		{
			ss[ShaderType::Vertex] << line << "\n";
		}
	}
	else
	{
		std::cout << "Unable to open shader file." << std::endl;
	}
	vertexShader.close();

	std::ifstream fragmentShader(fragmentPath);
	if (fragmentShader.is_open())
	{
		std::string line;
		while (std::getline(fragmentShader, line))
		{
			ss[ShaderType::Fragment] << line << "\n";
		}
	}
	else
	{
		std::cout << "Unable to open shader file." << std::endl;
	}
	fragmentShader.close();

	return { ss[0].str(), ss[1].str() };
}
