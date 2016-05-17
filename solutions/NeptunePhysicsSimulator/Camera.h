#ifndef CAMERA_H
#define CAMERA_H

#include "GL/glew.h"
#include <glm/glm.hpp>

class Camera
{

public:
	Camera();

	glm::mat4 GetViewMatrix();

	void ProcessKeyboard(const bool keys_[], GLfloat deltaTime_);
	void ProcessMouseMovement(GLfloat xoffset_, GLfloat yoffset_, GLboolean constrainPitch_ = true);

private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	GLfloat m_yaw;
	GLfloat m_pitch;

	void __UpdateCameraParameters();

};

#endif