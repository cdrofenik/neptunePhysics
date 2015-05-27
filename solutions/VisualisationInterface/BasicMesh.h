
#include <vector>
#include "glm\glm.hpp"

class BasicMesh {

public:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	BasicMesh(const char * path);
	~BasicMesh();

};