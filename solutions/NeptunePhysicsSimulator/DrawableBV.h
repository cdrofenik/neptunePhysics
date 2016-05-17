#ifndef DRAWABLEBV_H
#define DRAWABLEBV_H

#include "ContainerHelper.hpp"

#include <GL\glew.h>
#include "glm\glm.hpp"

#include <vector>

class DrawableBV
{
public:
	DrawableBV() {}
	~DrawableBV() {}

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

class DrawableAABB : public DrawableBV
{
public:
	DrawableAABB(const glm::vec3& minValues, const glm::vec3& maxValues);
	~DrawableAABB() { }

private:
	void __GenerateBoundingAABB(const glm::vec3& minValues, const glm::vec3& maxValues);
};

class DrawableSphere : public DrawableBV
{
public:
	DrawableSphere(const glm::vec3& minValues, const glm::vec3& maxValues);
	~DrawableSphere() {}

private:
	void __GenerateSphere(float radius, unsigned int rings, unsigned int sectors);

};

class DrawablePlane : public DrawableBV
{
public:
	DrawablePlane(const glm::vec3& minValues, const float& width, const float& length);
	~DrawablePlane() {}

private:
	void __GeneratePlane(const glm::vec3& startPoint, const float& width, const float& length);

};

#endif