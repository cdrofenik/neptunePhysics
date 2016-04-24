#include "ParticleSimulator.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ParticleSimulator::ParticleSimulator() {
	window = new OpenGLComponent(1024, 768);
};

ParticleSimulator::~ParticleSimulator() {
	window = nullptr;
};

void ParticleSimulator::initialize() {
	// Shader
	shader.AddShader("vertexShader.vert", ShaderType::VERTEX_SHADER);
	shader.AddShader("fragmentShader.frag", ShaderType::FRAGMENT_SHADER);
	shader.SetupProgram();
}

void ParticleSimulator::execute() {

	//Camera and perspective setup
	glm::mat4 model;
	model = glm::rotate(model, -45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view;
	glm::mat4 projection;
	projection = glm::perspective(45.0f, 1024 / (float)768, 0.1f, 100.0f);

	Mesh _mesh("..\\..\\external\\resources\\objects\\suzanne.obj");
	drawableList.push_back(_mesh);

	GLfloat lastFrame = 0;
	GLfloat deltaTime = 0;

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//shader.Use();

		// Transformation matrices
		//glm::mat4 view = camera.GetViewMatrix();
		//glUniformMatrix4fv(glGetUniformLocation(shader.programId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(glGetUniformLocation(shader.programId, "view"), 1, GL_FALSE, glm::value_ptr(view));

		//drawableList.at(0).Draw(shader, true);

		// Swap the buffers
		glfwSwapBuffers(window->getWindow());
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

}