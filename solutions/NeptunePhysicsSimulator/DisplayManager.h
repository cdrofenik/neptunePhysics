#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

// GLEW
#include <GL/glew.h>

// GLFW
#include <glfw3.h>

class DisplayManager
{
public:
	DisplayManager(const int& width_, const int& height_, const char* windowName_);
	~DisplayManager();

	void UpdateDisplay();
	void Enable(GLenum flag_);
	void CloseDisplay();

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	GLFWwindow* getWindow() { return m_window; }

private:
	int m_width;
	int m_height;

	GLFWwindow* m_window;

	int __CreateDisplay(const char* windowName_);
};

#endif