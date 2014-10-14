//#include "collisionHandler.h"
//
//#include <math.h>
//
//basicCollisionHandler::basicCollisionHandler()
//{
//}
//
//basicCollisionHandler::~basicCollisionHandler()
//{
//}
//
//basicCollisionHandler::AABB basicCollisionHandler::generateAABB(const GLfloat vertexArray[], int vertexSize)
//{
//	GLfloat minX = 100, minY = 100, minZ = 100, maxX = -100, maxY = -100, maxZ = -100;
//	for (size_t i = 0; i < vertexSize - 1; i+=3)
//	{
//		if (vertexArray[i] > maxX)
//			maxX = vertexArray[i];
//		else if (vertexArray[i] < minX)
//			minX = vertexArray[i];
//
//		if (vertexArray[i + 1] > maxY)
//			maxY = vertexArray[i + 1];
//		else if (vertexArray[i + 1] < minY)
//			minY = vertexArray[i + 1];
//
//		if (vertexArray[i + 2] > maxZ)
//			maxZ = vertexArray[i + 2];
//		else if (vertexArray[i + 2] < minZ)
//			minZ = vertexArray[i + 2];
//	}
//
//	float dx = (maxX - minX)/2;
//	float dy = (maxY - minY)/2;
//	float dz = (maxZ - minZ)/2;
//
//	AABB res = AABB();
//	res.center = glm::vec3(dx, dy, dz);
//	res.dx = dx;
//	res.dy = dy;
//	res.dz = dz;
//
//	char buffer[50];
//	sprintf(buffer, "Center(%f, %f, %f) created", dx, dy, dz);
//	printf("Created object center: %s \n", buffer);
//
//	return res;
//}
//
//basicCollisionHandler::AABB basicCollisionHandler::updateAABB(AABB& a, glm::mat4 modelMatrix)
//{
//	glm::vec4 res = modelMatrix * glm::vec4(1, 1, 1, 1);
//	a.center.x = res.x;
//	a.center.y = res.y;
//	a.center.z = res.z;
//
//	return a;
//}
//
//int basicCollisionHandler::testAABBAABB(AABB a, AABB b)
//{
//	int r;
//	r = a.dx + b.dx; if ((unsigned short)(a.center.x - b.center.x + r) > r + r) return 0;
//	r = a.dy + b.dy; if ((unsigned short)(a.center.y - b.center.y + r) > r + r) return 0;
//	r = a.dz + b.dz; if ((unsigned short)(a.center.z - b.center.z + r) > r + r) return 0;
//
//	char buffer[100];
//	//sprintf(buffer, "Center A(%d,%d,%d) tested. \n Center B(%d,%d,%d) tested.", a.center.x, a.center.y, a.center.z, b.center.x, b.center.y, b.center.z);
//	//printf("Centers are at \n %s", buffer);
//	return 1;
//}