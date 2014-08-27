#ifndef NEPTUNE_OBJECTLOADER_H
#define NEPTUNE_OBJECTLOADER_H

// Include GLM
#include <glm\glm.hpp>

#include <vector>


bool loadAssImp(
	const char * path,
	std::vector<unsigned short> & indices,
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals
	);

#endif