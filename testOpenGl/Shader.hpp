#pragma once
#include "util.hpp"
class Shader
{
private:
	unsigned int m_id;
	void createShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	unsigned int compileShader(unsigned int shaderType, const std::string& source);
	std::string readFileToString(const std::string& path);
public:
	unsigned int getID();
	void bindShader();

	void Uniform1f(const std::string& name, float p1);
	void Uniform1i(const std::string& name, int p1);

	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();
};

