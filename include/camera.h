#ifndef NEPTUNE_CAMERA_H
#define NEPTUNE_CAMERA_H

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm\glm.hpp>

class Camera {

	//TODO: Documentation

public:
	Camera() : position(glm::vec3(-2, -2, 6)), direction(glm::vec3(0, 0, 0)), up(glm::vec3(0, 1, 0)), speed(3.0f), mouseSpeed(0.005f), horizontalAngle(-4.05f), verticalAngle(0.9f) {}

	void setMouseToVisible(GLFWwindow* window, const bool& value);
	
	void updateCamera(GLFWwindow* window);

	glm::mat4 getProjectionMatrix() { return projectionMatrix; }
	glm::mat4 getViewMatrix() { return viewMatrix; }

	//TODO:
	//void setPosition(const glm::vec3& pos);
	//void setDirection(const glm::vec3& direcVector);
	//void setHorizontalAngle(const float& hAngle);
	//void setVerticalAngle(const float& vAngle);
	//void setMouseSpeed(const float& mSpeed);
	//void setSpeed(const float& spd);

private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;

	float horizontalAngle;
	float verticalAngle;

	float speed;
	float mouseSpeed;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	glm::mat4 _getProjectionMatrix(float FoV, float aspectRatio, float zNear, float zFar);
};

#endif