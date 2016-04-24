#ifndef WINDOWCOMPONENT_H
#define WINDOWCOMPONENT_H

// GLEW
#include <GL/glew.h>

// GLFW
#include <glfw3.h>

class OpenGLComponent
{
public:
	OpenGLComponent(const int& _width, const int& _height) :
		m_width(_width), m_height(_height) {
		initializeWindow();
	}
	~OpenGLComponent() {
		window = nullptr;
	};

	GLFWwindow* getWindow() { return window; }

private:
	int m_width = 0;
	int m_height = 0;

	GLFWwindow* window;

	int initializeWindow();
};


#endif