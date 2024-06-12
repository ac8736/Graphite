#pragma once
#include <glm/glm.hpp>
#include <string>

struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const ShaderSource& shaderSource);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, const glm::vec4& value) const;

	const unsigned int GetId() const;

	unsigned int CompileShader(unsigned int type, const std::string& shaderSource);

	static ShaderSource ParseShaders(const std::string& vertexPath, const std::string& fragmentPath);
private:
	unsigned int m_Id;
};

