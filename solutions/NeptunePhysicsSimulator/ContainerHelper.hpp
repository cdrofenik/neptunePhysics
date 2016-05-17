#ifndef CONTAINERHELPER_HPP
#define CONTAINERHELPER_HPP

#include "math/npMatrix3x4.h"
#include "math/npMatrix4.hpp"

#include <GL\glew.h>

#include "glm\glm.hpp"

#include <string>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct BVVertex {
	glm::vec3 position;
	glm::vec3 color;
};

struct Mesh{

	std::vector<Vertex> vertices_;
	std::vector<GLuint> indices_;

	glm::vec3 maxValueVector;
	glm::vec3 minValueVector;
};

struct MeshModel
{
	MeshModel()
	{
		vaoId = 0;
		textureId = 0;
		length = 0;

		minVector = glm::vec3(999, 999, 999);
		maxVector = glm::vec3(-999, -999, -999);
	}

	GLuint vaoId;
	GLuint textureId;
	GLuint length;

	glm::vec3 minVector;
	glm::vec3 maxVector;
};

struct RawModel {
	
public:

	RawModel() {};

	GLuint vaoId;
	GLuint vboId;
	GLuint eboId;
	int length;
};

struct Light
{
	glm::vec3 position;
	glm::vec3 color;
};

#endif