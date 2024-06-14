#pragma once
#include <string>

class Texture2D
{
public:
	Texture2D(const std::string& textureFile);
	~Texture2D();

	void Bind(unsigned int unit = 0) const;
	void Unbind() const;

	inline const unsigned int GetId() const { return m_Id; }

	unsigned int GenTexture(const std::string& textureFile);
private:
	unsigned int m_Id;
};
