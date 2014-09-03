// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL\glew.h>

class basicCollisionHandler
{
public:
	struct AABB{
		glm::vec3 center;
		float dx;
		float dy;
		float dz;
	};

	basicCollisionHandler();
	~basicCollisionHandler();

	AABB generateAABB(const GLfloat vertexArray[], int vertexSizeS);

	AABB updateAABB(AABB& a, glm::mat4 modelMatrix);

	int testAABBAABB(AABB a, AABB b);

private:
	
	 
};
