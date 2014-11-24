#include "../../../src/common/npVector.hpp"
#include "../../../src/common/npPoint.hpp"

#include <vector>

#include "wx/glcanvas.h"

struct face {
	std::vector<int> vertex;
	std::vector<int> texture;
	std::vector<int> normal;
};

class TriangleMesh
{
public:

	TriangleMesh() : vertices(std::vector<npVector3f>()),
		texcoords(std::vector<npPoint2f>()),
		normals(std::vector<npPoint3f>()),
		faces(std::vector<face>()){}
	~TriangleMesh() {
		glDeleteLists(list, 1);
	}

	void createWavefrontMesh(const char* filepath);

	void render();

private:
	char* objectName;
	std::vector<npVector3f> vertices;
	std::vector<npPoint2f> texcoords;
	std::vector<npPoint3f> normals;
	std::vector<face> faces;
	GLuint list;

};