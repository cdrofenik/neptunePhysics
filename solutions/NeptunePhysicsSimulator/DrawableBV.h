#ifndef DRAWABLEBV_H
#define DRAWABLEBV_H

#include "Collision\CollisionShapes\npCollisionShape.h"
#include "Collision\CollisionShapes\npBoxShape.h"
#include "Collision\CollisionShapes\npSphereShape.h"

#include "ContainerHelper.hpp"

#include <GL\glew.h>
#include "glm\glm.hpp"

#include <vector>

class DrawableShape
{
public:
	DrawableShape() {}
	~DrawableShape() {}

	void Clear();

	GLuint getVAO() { return m_vao; }
	int getVAOLength() { return m_indices.size(); }

protected:
	GLuint m_vao, m_vbo, m_ebo;

	std::vector<BVVertex> m_vertices;
	std::vector<int> m_indices;

	glm::vec3 __GenerateRandomColor();
	void __Init();
};

class Box : public DrawableShape
{
public:
	Box(const NeptunePhysics::npVector3r &minValues, const NeptunePhysics::npVector3r &maxValues);
	Box(const glm::vec3 &minValues, const glm::vec3 &maxValues);
	~Box() { }

private:
	void __GenerateBoundingAABB(const glm::vec3& minValues, const glm::vec3& maxValues);
};

class Sphere : public DrawableShape
{
public:
	Sphere(const glm::vec3 &minValues, const glm::vec3 &maxValues);
	Sphere(const NeptunePhysics::npVector3r &center, const NeptunePhysics::npReal &radius);
	~Sphere() {}

private:
	void __GenerateSphere(NeptunePhysics::npReal radius, unsigned int rings, unsigned int sectors);

};

class Plane : public DrawableShape
{
public:
	Plane(const glm::vec3& minValues, const float& width, const float& length);
	~Plane() {}

private:
	void __GeneratePlane(const glm::vec3& startPoint, const float& width, const float& length);

};

DrawableShape GetDrawableShape(NeptunePhysics::npCollisionShape* _shape);

#endif