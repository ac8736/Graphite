#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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

	void SetUniform1i(const std::string& name, int value) const;

	void SetUniform3f(const std::string& name, const glm::vec3& value) const;
	void SetUniform4f(const std::string& name, const glm::vec4& value) const;

	void SetUniformMatrix4fv(const std::string& name, const glm::mat4& value) const;

	inline const unsigned int GetId() const { return m_Id; }

	unsigned int CompileShader(unsigned int type, const std::string& shaderSource);

	static ShaderSource ParseShaders(const std::string& vertexPath, const std::string& fragmentPath);
private:
	unsigned int m_Id;
};

