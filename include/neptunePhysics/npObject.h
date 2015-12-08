#ifndef NEPTUNE_NPOBJECT_H
#define NEPTUNE_NPOBJECT_H

#include "npVector.hpp"
#include "npPoint.hpp"

#include <vector>

struct face {
	std::vector<int> vertex;
	std::vector<int> texture;
	std::vector<int> normal;
};

class npObject
{
public:
	char* objectName;
	std::vector<npVector3f> vertices;
	std::vector<npPoint2f> texcoords;
	std::vector<npVector3f> normals;
	std::vector<face> faces;

	npObject(): vertices(std::vector<npVector3f>()),
				uvs(std::vector<npPoint2f>()),
				normals(std::vector<npVector3f>()) {}

};


#endif