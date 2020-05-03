#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#define DELETA(x) if(x!=nullptr) {delete[] x;x=nullptr;}
#define FORI(name, Length,code) {for (int name = 0; name < Length; ++name){code}}
#ifdef DEBUG
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();x;ASSERT(!GLShowErrors(__LINE__, __FILE__));
#define LOGF(name,truc) {std::ofstream out; out.open("log/"+name, std::ios_base::app); out truc }
static void GLClearError() {
	GLenum error = glGetError();
	while (error != GL_NO_ERROR) {
		std::cout << "[opengl error],  {" << error << "}" << std::endl;
		error = glGetError();
	}
}
static bool GLShowErrors(int line, const char file[]) {
	bool errors = false;
	while (GLenum error = glGetError()) {
		std::cout << "[opengl error], comes from "<< file <<" at line " <<line <<" {" << error << ")" << std::endl;
		errors = true;
	}
	return errors;
}
#else// DEBUG end
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();x;ASSERT(!GLShowErrors(__LINE__, __FILE__));
static void GLClearError() {
	while (glGetError() != GL_NO_ERROR) {
	}
}
static bool GLShowErrors(int line, const char file[]) {
	if (GLenum error = glGetError())
		return true;
	return false;
}
#endif 
