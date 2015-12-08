#ifndef CAMERA_H
#define CAMERA_H

#include "GL/glew.h"

#include "glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{

public:
	Camera() :
		position(glm::vec3(0.0f, 0.0f, 3.0f)),
		worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
		front(glm::vec3(0.0f, 0.0f, -1.0f)),
		yaw(YAW),
		pitch(PITCH)
	{
		this->UpdateCameraParameters();
	}

	const GLfloat YAW = -90.0f;
	const GLfloat PITCH = 0.0f;
	const GLfloat SPEED = 3.0f;
	const GLfloat SENSITIVTY = 0.1f;
	const GLfloat ZOOM = 45.0f;

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(this->position, this->position + this->front, this->up);
	}

	void ProcessKeyboard(const bool keys[], GLfloat deltaTime)
	{
		// SPEED * deltaTime = Velocity

		if (keys[GLFW_KEY_W])
			this->position += this->front * SPEED * deltaTime; 
		if (keys[GLFW_KEY_S])
			this->position -= this->front * SPEED * deltaTime;
		if (keys[GLFW_KEY_A])
			this->position -= this->right * SPEED * deltaTime;
		if (keys[GLFW_KEY_D])
			this->position += this->right * SPEED * deltaTime;
	}

	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= SENSITIVTY;
		yoffset *= SENSITIVTY;

		this->yaw += xoffset;
		this->pitch += yoffset;

		if (constrainPitch)
		{
			if (this->pitch > 89.0f)
				this->pitch = 89.0f;
			if (this->pitch < -89.0f)
				this->pitch = -89.0f;
		}

		this->UpdateCameraParameters();
	}

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	void UpdateCameraParameters()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->front = glm::normalize(front);

		// Also re-calculate the Right and Up vector
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}

};

#endif