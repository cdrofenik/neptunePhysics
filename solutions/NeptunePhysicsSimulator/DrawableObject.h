#ifndef RIGIDBODYMESH_H
#define RIGIDBODYMESH_H

#include "Shader.hpp"

#include "collision/npRigidBody.h"

#include <GL\glew.h>

#include "glm\glm.hpp"

// ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <vector>

using namespace NeptunePhysics;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	std::string type;
	aiString path;
};

///////////////////////////////////////////////////////////////////////

class DrawableInterface
{
public:
	virtual void Init() = 0;
	virtual void Draw(Shader _shader, bool _displayWireframe) = 0;
	virtual void Clear() = 0;

};

///////////////////////////////////////////////////////////////////////

class DrawableObject : public DrawableInterface
{
public:
	DrawableObject() {}
	~DrawableObject() {}

	std::vector<Vertex> vertices_;
	std::vector<GLuint> indices_;
	std::vector<Texture> textures_;

	virtual void Init();
	virtual void Draw(Shader _shader, bool _displayWireframe);
	virtual void Clear();

private:
	GLuint vao_, vbo_, ebo_;

};

//////////////////////////////////////////////////////////////////////

class Mesh : public DrawableObject
{
public:
	Mesh(GLchar* _path);
	~Mesh() { }

	glm::vec3 getMaxValues() { return maxValues; }
	glm::vec3 getMinValues() { return minValues; }

private:
	//Min & max data
	glm::vec3 maxValues;
	glm::vec3 minValues;

	void CheckMinMaxValues(const glm::vec3& _currentVector, glm::vec3& _minValues, glm::vec3& _maxValues);

	void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	//Function expects one child of one mesh - complex meshes will be ignored
	void ProcessNode(aiNode* node, const aiScene* scene);

	//Processes an input file
	void LoadFromFile(GLchar* path);
};

///////////////////////////////////////////////////////////////////////

class Sphere : public DrawableObject
{
public:
	Sphere(const glm::vec3& minValues, const glm::vec3& maxValues);
	~Sphere() { }

private:
	void GenerateSphere(float radius, unsigned int rings, unsigned int sectors);
};

///////////////////////////////////////////////////////////////////////

class Box : public DrawableObject
{
public:
	Box(const glm::vec3& minValues, const glm::vec3& maxValues);
	~Box() { }
private:
	void GenerateBox(const glm::vec3& minValues, const glm::vec3& maxValues);
};
#endif