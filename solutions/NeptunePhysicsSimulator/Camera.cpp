#include "Camera.h"

#include "glfw3.h"
#include <glm/gtc/matrix_transform.hpp>

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVTY = 0.1f;
const GLfloat ZOOM = 45.0f;

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->m_position, this->m_position + this->m_front, this->m_up);
}

void Camera::ProcessKeyboard(const bool keys[], GLfloat deltaTime)
{
	// SPEED * deltaTime = Velocity

	if (keys[GLFW_KEY_W])
		this->m_position += this->m_front * SPEED * deltaTime;
	if (keys[GLFW_KEY_S])
		this->m_position -= this->m_front * SPEED * deltaTime;
	if (keys[GLFW_KEY_A])
		this->m_position -= this->m_right * SPEED * deltaTime;
	if (keys[GLFW_KEY_D])
		this->m_position += this->m_right * SPEED * deltaTime;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
	xoffset *= SENSITIVTY;
	yoffset *= SENSITIVTY;

	this->m_yaw += xoffset;
	this->m_pitch += yoffset;

	if (constrainPitch)
	{
		if (this->m_pitch > 89.0f)
			this->m_pitch = 89.0f;
		if (this->m_pitch < -89.0f)
			this->m_pitch = -89.0f;
	}

	__UpdateCameraParameters();
}

void Camera::__UpdateCameraParameters()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
	front.y = sin(glm::radians(this->m_pitch));
	front.z = sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
	this->m_front = glm::normalize(front);

	// Also re-calculate the Right and Up vector
	this->m_right = glm::normalize(glm::cross(this->m_front, this->m_worldUp));
	this->m_up = glm::normalize(glm::cross(this->m_right, this->m_front));
}

Camera::Camera() :	
	m_position(glm::vec3(0.0f, 0.0f, 3.0f)),
	m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_yaw(YAW), m_pitch(PITCH)
{
	__UpdateCameraParameters();
}