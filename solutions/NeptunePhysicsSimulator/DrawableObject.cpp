#include "DrawableObject.h"

//ASSIMP
#include <assimp/postprocess.h>


void DrawableObject::Init()
{
	glGenVertexArrays(1, &this->vao_);
	glGenBuffers(1, &this->vbo_);
	glGenBuffers(1, &this->ebo_);

	glBindVertexArray(this->vao_);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);

	glBufferData(GL_ARRAY_BUFFER, this->vertices_.size() * sizeof(Vertex), &this->vertices_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices_.size() * sizeof(GLuint), &this->indices_[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void DrawableObject::Draw(Shader _shader, bool _displayWireframe)
{
	glPolygonMode(GL_FRONT_AND_BACK, _displayWireframe ? GL_LINE : GL_FILL);

	// Draw mesh
	glBindVertexArray(this->vao_);
	glDrawElements(GL_TRIANGLES, this->indices_.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void DrawableObject::Clear()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
	glDeleteBuffers(1, &ebo_);
}

///////////////////////////////////////////////////////////////////////

void Mesh::CheckMinMaxValues(const glm::vec3& _currentVector, glm::vec3& _minValues, glm::vec3& _maxValues)
{
	if (_currentVector.x < _minValues.x) { _minValues.x = _currentVector.x; }
	else if (_currentVector.x > _maxValues.x) { _maxValues.x = _currentVector.x; }

	if (_currentVector.y < _minValues.y) { _minValues.y = _currentVector.y; }
	else if (_currentVector.y > _maxValues.y) { _maxValues.y = _currentVector.y; }

	if (_currentVector.z < _minValues.z) { _minValues.z = _currentVector.z; }
	else if (_currentVector.z > _maxValues.z) { _maxValues.z = _currentVector.z; }
}

void Mesh::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	maxValues = glm::vec3(-9999999, -9999999, -9999999);
	minValues = glm::vec3(9999999, 9999999, 9999999);

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;
		// Positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		CheckMinMaxValues(vector, minValues, maxValues);

		vertex.Position = vector;
		// Normals
		if (mesh->mNormals != NULL) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}

		// Texture Coordinates
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices_.push_back(vertex);
	}

	// Process indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices_.push_back(face.mIndices[j]);
	}
}

void Mesh::ProcessNode(aiNode* node, const aiScene* scene)
{
	if (node->mNumMeshes == 1) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];
		this->ProcessMesh(mesh, scene);
	}
	else if (node->mNumChildren == 1) {
		this->ProcessNode(node->mChildren[0], scene);
	}
	else {
		//Log_DEBUG("[Mesh.hpp]", "ProcessNode function", "Meshes count 0 or greater then 1");
	}
}

void Mesh::LoadFromFile(GLchar* path) {
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("ERROR::ASSIMP:: %s\n", import.GetErrorString());
		return;
	}

	//this->directory = path.substr(0, path.find_last_of('/'));

	this->ProcessNode(scene->mRootNode, scene);
}

Mesh::Mesh(GLchar* _path)
{
	LoadFromFile(_path);
	Init();
}

///////////////////////////////////////////////////////////////////////

Sphere::Sphere(const glm::vec3& minValues, const glm::vec3& maxValues)
{
	auto distX = maxValues.x - minValues.x;
	auto distY = maxValues.y - minValues.y;
	auto distZ = maxValues.z - minValues.z;

	auto radius = distX > distY ? distX : distY;
	radius = radius > distZ ? radius : distZ;

	GenerateSphere(radius/2, 12, 24);
	Init();
}

void Sphere::GenerateSphere(float radius, unsigned int rings, unsigned int sectors)
{
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	//vertices_.resize(rings * sectors * 3 * 3 * 2);
	for (r = 0; r < rings; r++)
		for (s = 0; s < sectors; s++) {
			float const y = sin(-M_PI_2 + NP_PI * r * R);
			float const x = cos(2 * NP_PI * s * S) * sin(NP_PI * r * R);
			float const z = sin(2 * NP_PI * s * S) * sin(NP_PI * r * R);

			Vertex vertex;

			//Position
			glm::vec3 vector;
			vector.x = x * radius;
			vector.y = y * radius;
			vector.z = z * radius;
			vertex.Position = vector;

			//Normal
			glm::vec3 normal;
			normal.x = x;
			normal.y = y;
			normal.z = z;
			vertex.Normal = normal;

			//Texture
			vertex.TexCoords = glm::vec2(s*S, r*R);

			vertices_.push_back(vertex);
	}

	indices_.resize(rings * sectors * 6);
	for (r = 0; r < rings - 1; r++)
		for (s = 0; s < sectors - 1; s++) {
			indices_.push_back(r * sectors + s);
			indices_.push_back(r * sectors + (s + 1));
			indices_.push_back((r + 1) * sectors + (s + 1));

			indices_.push_back((r + 1) * sectors + s);
			indices_.push_back((r + 1) * sectors + (s + 1));
			indices_.push_back(r * sectors + s);
	}
}

///////////////////////////////////////////////////////////////////////

Box::Box(const glm::vec3& minValues, const glm::vec3& maxValues)
{
	GenerateBox(minValues, maxValues);
	Init();
}

void Box::GenerateBox(const glm::vec3& minValues, const glm::vec3& maxValues)
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
	//vertices_.reserve(24 * 3 * 3 * 2);
	for (size_t i = 0; i < 22; i += 3)
	{
		Vertex vertex;

		//Position
		glm::vec3 vector;
		vector.x = vertex_data[i];
		vector.y = vertex_data[i + 1];
		vector.z = vertex_data[i + 2];

		vertex.Position = vector;

		//Texture
		vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices_.push_back(vertex);
	}

	float indices_data[] = {
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
	indices_.clear();
	indices_.reserve(36);
	for (size_t i = 0; i < 36; i++)
	{
		indices_.push_back(indices_data[i]);
	}
}
