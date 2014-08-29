#include "glUtils/camera.hpp"


void Camera::updateCamera(GLFWwindow* window)
{
	static double lastTime = glfwGetTime(); // glfwGetTime is called only once, the first time this function is called

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime); // Compute time difference between current and last frame

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Compute new orientation
	horizontalAngle -= mouseSpeed * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
		);

	// Up vector
	up = glm::vec3();
	glm::vec3 _up = glm::cross(right, direction);

	up = _up;

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}

	projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f); // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units

	//generate the camera matrix
	viewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

	//std::cout << "Current position: " << position.x << ", " << position.y << " , " << position.z << std::endl;
	//std::cout << "Current direction: " << direction.x << ", " << direction.y << " , " << direction.z << std::endl;
}

void Camera::setMouseToVisible(GLFWwindow* window, const bool& value)
{
	if (!value)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}