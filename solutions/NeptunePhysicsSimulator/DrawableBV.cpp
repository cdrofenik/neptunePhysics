#include "DrawableBV.h"

#include "math/npPrecision.hpp"

///////////////////////////////////////////////////////////////////////////
// DrawableBV


glm::vec3 DrawableBV::__GenerateRandomColor()
{
	return glm::vec3(0.5f, 0.5f, 0.0f);
}

void DrawableBV::__Init()
{
	glGenVertexArrays(1, &this->m_vao);

		glGenBuffers(1, &this->m_vbo);
		glGenBuffers(1, &this->m_ebo);

		glBindVertexArray(this->m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);

		glBufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(BVVertex), &this->m_vertices[0], GL_STATIC_DRAW);

		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BVVertex), (GLvoid*)0);
		// Vertex Texture Coords
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BVVertex), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_indices.size() * sizeof(GLuint), &this->m_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void DrawableBV::Clear()
{
	m_vertices.clear();
	m_indices.clear();

	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}

///////////////////////////////////////////////////////////////////////////
// DrawableAABB

void DrawableAABB::__GenerateBoundingAABB(const glm::vec3& minValues, const glm::vec3& maxValues)
{
	float vertex_data[] = {
		minValues.x, minValues.y, minValues.z, // bottom front left
		maxValues.x, minValues.y, minValues.z, // bottom front right
		minValues.x, maxValues.y, minValues.z, // top front left
		maxValues.x, maxValues.y, minValues.z, // top front right

		minValues.x, minValues.y, maxValues.z, // bottom back left
		maxValues.x, minValues.y, maxValues.z, // bottom back right
		minValues.x, maxValues.y, maxValues.z, // top back left
		maxValues.x, maxValues.y, maxValues.z // top back right
	};

	glm::vec3 color = __GenerateRandomColor();

	//m_vertices.reserve(24 * 3 * 3 * 2);
	for (size_t i = 0; i < 22; i += 3)
	{
		BVVertex vertex;

		//Position
		glm::vec3 vector;
		vector.x = vertex_data[i];
		vector.y = vertex_data[i + 1];
		vector.z = vertex_data[i + 2];

		vertex.position = vector;

		//Color
		vertex.color = color;

		m_vertices.push_back(vertex);
	}

	int m_indicesdata[] = {
		0, 2, 3,
		3, 0, 1,
		1, 3, 5,
		5, 7, 3,
		3, 6, 2,
		2, 4, 6,
		6, 7, 4,
		4, 5, 1,
		1, 4, 0,
		7, 5, 4,
		6, 7, 3,
		4, 2, 0
	};
	m_indices.clear();
	m_indices.reserve(36);
	for (size_t i = 0; i < 36; i++)
	{
		m_indices.push_back(m_indicesdata[i]);
	}
}

DrawableAABB::DrawableAABB(const glm::vec3& minValues, const glm::vec3& maxValues)
{
	__GenerateBoundingAABB(minValues, maxValues);
	__Init();
}


///////////////////////////////////////////////////////////////////////////
// DrawableSphere

void DrawableSphere::__GenerateSphere(float radius, unsigned int rings, unsigned int sectors)
{
	float const R = 1.0f / (float)(rings - 1.0f);
	float const S = 1.0f / (float)(sectors - 1.0f);
	unsigned int r, s;

	//m_vertices.resize(rings * sectors * 3 * 3 * 2);
	for (r = 0; r < rings; r++)
		for (s = 0; s < sectors; s++) {
			float const y = sin(-M_PI_2 + NP_PI * r * R);
			float const x = cos(2 * NP_PI * s * S) * sin(NP_PI * r * R);
			float const z = sin(2 * NP_PI * s * S) * sin(NP_PI * r * R);

			BVVertex vertex;

			//Position
			glm::vec3 vector;
			vector.x = x * radius;
			vector.y = y * radius;
			vector.z = z * radius;
			vertex.position = vector;

			//Color
			vertex.color = __GenerateRandomColor();

			m_vertices.push_back(vertex);
		}

	m_indices.resize(rings * sectors * 6);
	for (r = 0; r < rings - 1; r++)
		for (s = 0; s < sectors - 1; s++) {
			m_indices.push_back(r * sectors + s);
			m_indices.push_back(r * sectors + (s + 1));
			m_indices.push_back((r + 1) * sectors + (s + 1));

			m_indices.push_back((r + 1) * sectors + s);
			m_indices.push_back((r + 1) * sectors + (s + 1));
			m_indices.push_back(r * sectors + s);
		}
}

DrawableSphere::DrawableSphere(const glm::vec3& minValues, const glm::vec3& maxValues)
{
	auto distX = maxValues.x - minValues.x;
	auto distY = maxValues.y - minValues.y;
	auto distZ = maxValues.z - minValues.z;

	auto radius = distX > distY ? distX : distY;
	radius = radius > distZ ? radius : distZ;

	__GenerateSphere(radius / 2, 12, 32);
	__Init();
}

///////////////////////////////////////////////////////////////////////////
// DrawableSphere

void DrawablePlane::__GeneratePlane(const glm::vec3& startPoint, const float& width, const float& length)
{
	float vertex_data[] = {
		startPoint.x, startPoint.y, startPoint.z,
		startPoint.x + width, startPoint.y, startPoint.z,
		startPoint.x + width, startPoint.y, startPoint.z + length,
		startPoint.x, startPoint.y, startPoint.z + length
	};

	for (size_t i = 0; i < 12; i += 3)
	{
		BVVertex vertex;

		//Position
		glm::vec3 vector;
		vector.x = vertex_data[i];
		vector.y = vertex_data[i + 1];
		vector.z = vertex_data[i + 2];

		vertex.position = vector;

		//Color
		vertex.color = __GenerateRandomColor();

		m_vertices.push_back(vertex);
	}

	float m_indicesdata[] = {
		0, 1, 2,
		2, 3, 0
	};
	m_indices.clear();
	m_indices.reserve(6);
	for (size_t i = 0; i < 6; i++)
	{
		m_indices.push_back(m_indicesdata[i]);
	}
}

DrawablePlane::DrawablePlane(const glm::vec3& minValues, const float& width, const float& length)
{
	__GeneratePlane(minValues, width, length);
	__Init();
}