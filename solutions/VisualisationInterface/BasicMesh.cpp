#include "BasicMesh.h"
#include "..\..\external\common\objloader.hpp"

BasicMesh::BasicMesh(const char * fPath) {

	vertices = std::vector<glm::vec3>();
	uvs = std::vector<glm::vec2>();
	normals = std::vector<glm::vec3>();

	bool res = loadOBJ(fPath, vertices, uvs, normals);
}

BasicMesh::~BasicMesh() {
	vertices.clear();
	normals.clear();
	uvs.clear();
}