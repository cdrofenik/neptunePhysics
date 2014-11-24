#ifndef NEPTUNE_OBJLOADER_H
#define NEPTUNE_OBJLOADER_H

#include "../common/npPoint.hpp"
#include "../common/npVector.hpp"
#include "../common/npObject.h"

#include <vector>
#include <map>
#include <memory>
#include <string>

//! 
//!... Index used for VBO
//!
struct VIndex {
	int v, vt, vn;
	VIndex() {};
	VIndex(int vertexIndice) : v(v), vt(v), vn(v) {};	//TODO check if it works
	VIndex(int v, int vt, int vn) : v(v), vt(vt), vn(vn) {};
};

class ObjReader
{

public:
	ObjReader() {}

	bool readObjFile(const char *filename,
					npObject& object);
};

#endif