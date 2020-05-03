#include "util.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexAndIndexBuffer.hpp"
#include "staticTiledMap.hpp"
#include "map.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "extern/stb_image.hpp"
#define CAP_FPS 75

/*
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();x;ASSERT(!GLShowErrors());
static void GLClearError() {
	while (glGetError() != GL_NO_ERROR) {
	}
}
static bool GLShowErrors() {
	bool errors = false;
	while (GLenum error = glGetError()) {
		std::cout << "[opengl error] {" << error << ")" << std::endl;
		errors = true;
	}
	return errors;
}*/
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void toggleFullScreen(GLFWwindow* window) {
	static bool fullscreen = false;
	if (fullscreen) {
		glfwSetWindowMonitor(window,NULL,200,200,640,560,NULL);
#ifdef DEBUG
		std::cout << "fullscreen off ! " << std::endl;
#endif // DEBUG
	}
	else {
		int width;
		int height;
		int xpos;
		int ypos;
		GLFWmonitor * 	monitor = glfwGetPrimaryMonitor();
		glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);
		glfwSwapInterval(1);
#ifdef DEBUG
		std::cout << "monitor : " << xpos << ":" << ypos << "sizes (" << width << "," << height << ")" << std::endl;
#endif // DEBUG

		
		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), xpos, ypos, width, height, NULL);
	}
	fullscreen = !fullscreen;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
		toggleFullScreen(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
int main(void)
{
	
	std::string vertexShader ="res/shaders/vertex/vertex01.glsl";
	std::string fragmentShader = "res/shaders/fragment/fragment01.glsl";
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	unsigned int indexes[] = {
		0,1,2,
		2,3,0
	};

	float vertices[] = {
		-1.0,-1.0, 0.0, 0.0,
		-1.0, 1.0, 0.0, 1.0,
		 1.0, 1.0, 1.0, 1.0,
		 1.0,-1.0, 1.0, 0.0

	};
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 560, "Hello World",NULL, NULL);

	if (!window)
	{
		std::cout << glfwGetError(NULL) << std::endl;
		glfwTerminate();
		return -1;
	}
	std::cout << "window is successfully created" << std::endl;
	glfwWindowHint(GLFW_REFRESH_RATE, 15);
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
		std::cout << "glew not ok" << std::endl;
	else
	{
		
		laen::map<Texture> textures;
		std::cout << glGetString(GL_VERSION) << std::endl;
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetKeyCallback(window, key_callback);
		glfwSwapInterval(1);
		
		int shape[2] = { 2,2 };
		staticTiledMap stm("res/maps/map01.map", textures);
		stm.getCamera()->setWidth(16*5);
		//
		stm.getCamera()->setHeight(16 * 5);
		//VertexAndIndexBuffer vaib((int*)shape, 2,(float*) vertices,  16, GL_DYNAMIC_DRAW, (unsigned int*)indexes,6 );
		Shader shader(vertexShader, fragmentShader);
		shader.bindShader();
		Texture tex("res/texture/avatar.png");
		Texture tex2("res/texture/alakon.png");
		/* Loop until the user closes the window */
		
		while (!glfwWindowShouldClose(window))
		{
			auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			float actuaTime = time % 300000000;
			//std::cout << actuaTime << std::endl;
			
			shader.Uniform1f("time", actuaTime);
			shader.Uniform1i("u_texture", 0);
			stm.getCamera()->setX((time/100)%50);
			//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));
			//vaib.draw();
			/* Swap front and back buffers */
			stm.draw();
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
			auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			if (time2 - time <= 1000 / CAP_FPS) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 / CAP_FPS - (time2 - time) ));
			}
		}


		
	}
	glfwTerminate();
#ifdef DEBUG
	std::cin.get();
#endif // DEBUG

	return 0;
}