#include "DisplayManager.h"

//TODO Logging
#include <iostream>

int DisplayManager::__CreateDisplay(const char* windowName_)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW!\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Watchdog for bad coding habits
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS compatibility

	m_window = glfwCreateWindow(m_width, m_height, windowName_, nullptr, nullptr);
	if (m_window == nullptr)
	{
		fprintf(stderr, "Failed to open GLFW window!\n");
		glfwTerminate();
		return -1;
	}
	// Set OpenGL context as the current window object
	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW!\n");
		return -1;
	}

	glViewport(0, 0, m_width, m_height);

	return 1;
}

void DisplayManager::UpdateDisplay()
{
	// Swap the buffers
	glfwSwapBuffers(m_window);
}

void DisplayManager::Enable(GLenum flag_)
{
	glEnable(flag_);
}

void DisplayManager::CloseDisplay()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}

DisplayManager::DisplayManager(const int& width_, const int& height_, const char* windowName_) :
m_width(width_), m_height(height_) {
	__CreateDisplay(windowName_);
};

DisplayManager::~DisplayManager() {
	m_window = nullptr;
};