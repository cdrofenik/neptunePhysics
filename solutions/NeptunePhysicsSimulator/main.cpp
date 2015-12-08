#include "main.h"

#include "Camera.hpp"
#include "Shader.hpp"
#include "Model.hpp"

// GLEW
#include <GL/glew.h>

// GLFW
#include <glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

Camera gameCamera;

bool wireFrameMode = false;
bool keys[1024];
bool firstMouse = true;

GLfloat deltaTime = 0;
GLfloat lastFrame = 0;
double lastX;
double lastY;

// Keyboard input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//Wireframe mode
	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		wireFrameMode = !wireFrameMode;
		glPolygonMode(GL_FRONT_AND_BACK, wireFrameMode ? GL_LINE : GL_FILL);
	}
		
	//Close application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Resolves muliple buttons pressed at the same time
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

// Callback for mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	gameCamera.ProcessMouseMovement(xoffset, yoffset);
}

int main() {

	fprintf(stderr, "[Main] Starting simulator!\n");

#pragma region GLFW, Window & GLEW setup
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

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Neptune Physics Viewer", nullptr, nullptr);
	if (window == nullptr)
	{
		fprintf(stderr, "Failed to open GLFW window!\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Set OpenGL context as the current window object

	glewExperimental = GL_TRUE; // Needed in core profile 
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW!\n");
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);
#pragma endregion

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	glm::mat4 model;
	model = glm::rotate(model, -45.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view;

	glm::mat4 projection;
	projection = glm::perspective(45.0f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

	// Shader
	Shader mainShader;
	mainShader.AddShader("vertexShader.vert", ShaderType::VERTEX_SHADER);
	mainShader.AddShader("fragmentShader.frag", ShaderType::FRAGMENT_SHADER);
	mainShader.SetupProgram();

	Model _model("..\\..\\external\\resources\\objects\\suzanne.obj");

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents();
		gameCamera.ProcessKeyboard(keys, deltaTime);

		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mainShader.Use();   // <-- Don't forget this one!
		// Transformation matrices
		glm::mat4 projection = glm::perspective(45.0f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = gameCamera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(mainShader.programId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(mainShader.programId, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// Draw the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(mainShader.programId, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//ourModel.Draw(shader);

		_model.Draw(mainShader);

		// Swap the buffers
		glfwSwapBuffers(window); 
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}