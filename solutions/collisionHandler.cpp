#include "collisionHandler.h"

#include <math.h>

basicCollisionHandler::basicCollisionHandler()
{
}

basicCollisionHandler::~basicCollisionHandler()
{
}

basicCollisionHandler::AABB basicCollisionHandler::generateAABB(const GLfloat vertexArray[], int vertexSize)
{
	GLfloat minX = 100, minY = 100, minZ = 100, maxX = -100, maxY = -100, maxZ = -100;
	for (size_t i = 0; i < vertexSize - 1; i+=3)
	{
		if (vertexArray[i] > maxX)
			maxX = vertexArray[i];
		else if (vertexArray[i] < minX)
			minX = vertexArray[i];

		if (vertexArray[i + 1] > maxY)
			maxY = vertexArray[i + 1];
		else if (vertexArray[i + 1] < minY)
			minY = vertexArray[i + 1];

		if (vertexArray[i + 2] > maxZ)
			maxZ = vertexArray[i + 2];
		else if (vertexArray[i + 2] < minZ)
			minZ = vertexArray[i + 2];
	}

	float dx = (maxX - minX);
	float dy = (maxY - minY);
	float dz = (maxZ - minZ);

	AABB res = AABB();
	res.center = glm::vec3(dx, dy, dz);
	res.dx = dx / 2;
	res.dy = dy / 2;
	res.dz = dz / 2;

	return res;
}

basicCollisionHandler::AABB basicCollisionHandler::updateAABB(AABB& a, glm::mat4 modelMatrix)
{
	glm::vec4 res = modelMatrix * glm::vec4(1, 1, 1, 1);
	a.center.x = res.x;
	a.center.y = res.y;
	a.center.z = res.z;

	return a;
}

int basicCollisionHandler::testAABBAABB(AABB a, AABB b)
{
	/*printf("Center distance x: %d\n", abs(a.center.x - b.center.x));
	printf("Center distance y: %d\n", abs(a.center.y - b.center.y));
	printf("Center distance z: %d\n", abs(a.center.z - b.center.z));*/
	int r;
	r = a.dx + b.dx; if ((unsigned short)(a.center.x - b.center.x + r) > r + r) return 0;
	r = a.dy + b.dy; if ((unsigned short)(a.center.y - b.center.y + r) > r + r) return 0;
	r = a.dz + b.dz; if ((unsigned short)(a.center.z - b.center.z + r) > r + r) return 0;
	return 1;
}