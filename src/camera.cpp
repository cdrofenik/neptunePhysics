#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

glm::mat4 Camera::_getProjectionMatrix(float FoV, float aspectRatio, float zNear, float zFar)
{
	//generate projection matrix with the glm::perspective
	return glm::perspective(FoV, aspectRatio, zNear, zFar);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Camera::setMouseToVisible(GLFWwindow* window, const bool& value)
{
	if (!value)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}