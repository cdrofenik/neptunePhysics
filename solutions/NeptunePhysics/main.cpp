#include "../../src/common/npVector.hpp"
#include "../../src/serialize/ObjReader.h"

int main(int argc, char* argv[])
{

	ObjReader objR;

	std::vector<npPoint3f> out_vertices;
	std::vector<npPoint2f> out_uvs;
	std::vector<npPoint3f> out_normals;

	//objR.readObjFile("E:\\GitHub\\neptune-physics\\resources\\objects\\armadillo.obj", out_vertices, out_uvs, out_normals);

	return 0;
}
