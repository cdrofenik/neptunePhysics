#include "main.h"

#include "CameraComponent.hpp"
#include "ShaderComponent.hpp"
#include "DrawableObject.h"
#include "Utils.hpp"

// Neptune Physics
#include "neptunePhysics/math/npTransform.hpp"
#include "neptunePhysics/collision/npCollisionShape.h"
#include "neptunePhysics/core/npDiscreteDynamicsWorld.h"
#include "neptunePhysics/collision/npRigidBody.h"

// Logging
#include "logging\npLogging.hpp"

// Refactoring
#include "OpenGLComponent.h"

#include "core/npParticle.h"

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

#include "ParticleSimulator.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

using namespace NeptunePhysics;

CameraComponent gameCamera;

bool wireFrameMode = true;
bool pauseSimulation = false;
bool showBoundingVolumes = true;
bool keys[1024];
bool firstMouse = true;

GLdouble deltaTime = 0;
GLdouble lastFrame = 0;
double lastX;
double lastY;

//Create Manager struct as container for data
std::vector<DrawableObject> drawableList;

// Keyboard input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//Wireframe mode
	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		wireFrameMode = !wireFrameMode;
		glPolygonMode(GL_FRONT_AND_BACK, wireFrameMode ? GL_LINE : GL_FILL);
	}

	//Pause simulation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		pauseSimulation = !pauseSimulation;
	}

	//Pause simulation
	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		showBoundingVolumes = !showBoundingVolumes;
	}

	//Close application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Resolves muliple buttons pressed at the same 
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void initialize(npDiscreteDynamicsWorld* world, Mesh _mesh)
{
	int rigidBodyCount = 4;

	npVector3 Pos(0.0f, 2.75f, 0.0f);
	npVector3 veloPos(0, 0, 0);
	npVector3 accelPos(0, 0, 0);

	drawableList.clear();
	for (size_t i = 0; i < rigidBodyCount; i++)
	{
		npVector3 startPos = Pos + npVector3(i * 1.5f, i * 2.75f, 0.0f);

		npParticle tmpBody(startPos, veloPos, accelPos, 0.1, 10);
		//(20, startPos, veloPos, accelPos);
		if (i == 1) {
			tmpBody.m_acceleration = npVector3(0, -1.0f, 0);
		}
		else if (i == 0) {
			//tmpBody.m_velocity = npVector3(0, -1.0f, 0);
		}

		world->addParticle(tmpBody);

		Box drawnBody(_mesh.getMinValues(), _mesh.getMaxValues());
		drawableList.push_back(drawnBody);
	}

	//Earth plane (approx.)
	npParticle _tmpBody(npVector3(0.0f, 0.0f, 0.0f), veloPos, accelPos, 0.0f, 0.0f);
	world->addParticle(_tmpBody);

	Plane tmpPlane(glm::vec3(-50, 0, -50), 100, 100);
	drawableList.push_back(tmpPlane);

	world->addToForceRegistry();
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

	GLdouble xoffset = xpos - lastX;
	GLdouble yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	gameCamera.ProcessMouseMovement(xoffset, yoffset);
}

int main() {

	OpenGLComponent mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

	//Input handling
	glfwSetInputMode(mainWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(mainWindow.getWindow(), key_callback);
	glfwSetCursorPosCallback(mainWindow.getWindow(), mouse_callback);

	//Camera and perspective setup
	glm::mat4 model;
	model = glm::rotate(model, -45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view;
	glm::mat4 projection;
	projection = glm::perspective(45.0f, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);


	// Shader
	ShaderComponent mainShader;
	mainShader.AddShader("vertexShader.vert", ShaderType::VERTEX_SHADER);
	mainShader.AddShader("fragmentShader.frag", ShaderType::FRAGMENT_SHADER);
	mainShader.SetupProgram();

	// Loading mesh
	Mesh _mesh("..\\..\\external\\resources\\objects\\suzanne.obj");
	//drawableList.push_back(_mesh);

	//Initialize physics engine
	npDiscreteDynamicsWorld* world = new npDiscreteDynamicsWorld();
	initialize(world, _mesh);


	while (!glfwWindowShouldClose(mainWindow.getWindow()))
	{
		GLdouble currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents();
		gameCamera.ProcessKeyboard(keys, deltaTime);

		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mainShader.Use();
		// Transformation matrices
		glm::mat4 view = gameCamera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(mainShader.programId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(mainShader.programId, "view"), 1, GL_FALSE, glm::value_ptr(view));

		if (!pauseSimulation) {
			world->stepSimulation(deltaTime);
		}

		for (int i = 0; i < 5; i++) {

			auto rigidBdy = world->getParticle(i);

			//Position model based on rigid body position
			npTransform startPos;

			if (!pauseSimulation) {
				Log_DEBUG("main.cpp - 197", "Index", i);
				Log_DEBUG("main.cpp - 197", "Body position:", rigidBdy.m_position);
			}

			startPos.setOrigin(rigidBdy.m_position.x, rigidBdy.m_position.y, rigidBdy.m_position.z);
			startPos.setScale(0.5f, 0.5f, 0.5f);
			npMotionState mState = npMotionState(startPos.getTransformMatrix());

			glUniformMatrix4fv(glGetUniformLocation(mainShader.programId, "model"), 1, GL_FALSE, mState.GetStateMatrix4().transpose().m);

			if (showBoundingVolumes)
			{
				drawableList.at(i).Draw(mainShader, wireFrameMode);
			}

		}

		// Swap the buffers
		glfwSwapBuffers(mainWindow.getWindow());
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	for (auto& _drawable : drawableList)
		_drawable.Clear();

	drawableList.clear();

	return 0;
}