#include "Shader.hpp"
#include <fstream>
#include <string>


void Shader::createShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	unsigned int program, verShad, fraShad;
	GLCall(program = glCreateProgram());
#ifdef DEBUG
	std::cout << "creating shader ID=" << program << std::endl;
#endif
	std::string vertexShader, fragmentShader;
	vertexShader = readFileToString(vertexShaderPath);
	fragmentShader = readFileToString(fragmentShaderPath);
	GLCall(verShad = compileShader(GL_VERTEX_SHADER, vertexShader));
	GLCall(fraShad = compileShader(GL_FRAGMENT_SHADER, fragmentShader));
	GLCall(glAttachShader(program, verShad));
	GLCall(glAttachShader(program, fraShad));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));
	GLCall(glDeleteShader(verShad));
	GLCall(glDeleteShader(fraShad));
	this->m_id = program;
}

unsigned int Shader::compileShader(unsigned int shaderType, const std::string & source)
{
	unsigned int id;
	GLCall(id = glCreateShader(shaderType));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (!result) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "error while compiling the shader : " << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}

std::string Shader::readFileToString(const std::string & path)
{
	std::string line, out = "";
	std::ifstream file(path);
	while (getline(file, line)) {
		out += line + "\n";
	}
#ifdef DEBUG
	std::cout <<"reading all file : "<<   path << std::endl;
#endif
	return out;
}

unsigned int Shader::getID()
{
	return this -> m_id;
}

void Shader::bindShader()
{
	GLCall(glUseProgram(this->m_id));
}

void Shader::Uniform1f(const std::string & name, float p1)
{
	int location;
	GLCall(location = glGetUniformLocation(this->m_id, name.c_str()));
	GLCall(glUniform1f(location, p1));

}

void Shader::Uniform1i(const std::string & name, int p1)
{
	int location;
	GLCall(location = glGetUniformLocation(this->m_id, name.c_str()));
	GLCall(glUniform1i(location, p1));
}

Shader::Shader(const std::string & vertexShader, const std::string & fragmentShader)
{
	this->createShader(vertexShader, fragmentShader);
}





Shader::~Shader()
{
#ifdef DEBUG
	std::cout << "deleting shader, ID=" << this->m_id << std::endl;
#endif
	GLCall(glDeleteProgram(this ->m_id));
}
