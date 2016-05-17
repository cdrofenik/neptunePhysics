#include "ObjectLoader.h"

//ASSIMP
#include <assimp/postprocess.h>

ObjectLoader::ObjectLoader()
{
	std::vector<GLuint> m_vaos = std::vector<GLuint>();
	std::vector<GLuint> m_vbos = std::vector<GLuint>();
	std::vector<GLuint> m_ebos = std::vector<GLuint>();
}

ObjectLoader::~ObjectLoader()
{
}

GLuint ObjectLoader::__CreateVAO()
{
	GLuint vaoId;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);
	m_vaos.push_back(vaoId);

	return vaoId;
}

GLuint ObjectLoader::__CreateVBO(std::vector<Vertex> verticesData_)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesData_.size() * sizeof(Vertex), &verticesData_[0], GL_STATIC_DRAW);
	m_vbos.push_back(vbo);
	return vbo;
}

GLuint ObjectLoader::__BindIndices(std::vector<GLuint> indiciesData_)
{
	GLuint eboId;
	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesData_.size() * sizeof(GLuint), &indiciesData_[0], GL_STATIC_DRAW);
	m_ebos.push_back(eboId);
	return eboId;
}

GLuint ObjectLoader::__CreateVBO(GLfloat data_[], const int& dataSize_)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, dataSize_ * sizeof(GLfloat), data_, GL_STATIC_DRAW);
	m_vbos.push_back(vbo);

	return vbo;
}

GLuint ObjectLoader::__BindIndices(GLuint data_[], const int& dataSize_)
{
	GLuint eboId;
	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize_ * sizeof(GLuint), data_, GL_STATIC_DRAW);

	m_ebos.push_back(eboId);
	return eboId;
}

void ObjectLoader::__UnbindVAO()
{
	glBindVertexArray(0);
}

void ObjectLoader::__StoreDataInAttributeArray(const int& attribNumber_, const int& elementCount_,
	const GLenum& elementType_, const int& elementLength_, const int& startPos_)
{
	glVertexAttribPointer(attribNumber_, elementCount_, elementType_, GL_FALSE, elementLength_, (GLvoid*)startPos_);
}

//////////////////////////////////////////////////////////////////////////////
// ASSIMP .OBJ Loader

static inline void _CheckMinMaxValues(const glm::vec3& currentVector_, glm::vec3& minValues_, glm::vec3& maxValues_)
{
	if (currentVector_.x < minValues_.x) { minValues_.x = currentVector_.x; }
	else if (currentVector_.x > maxValues_.x) { maxValues_.x = currentVector_.x; }

	if (currentVector_.y < minValues_.y) { minValues_.y = currentVector_.y; }
	else if (currentVector_.y > maxValues_.y) { maxValues_.y = currentVector_.y; }

	if (currentVector_.z < minValues_.z) { minValues_.z = currentVector_.z; }
	else if (currentVector_.z > maxValues_.z) { maxValues_.z = currentVector_.z; }
}

void ObjectLoader::__ProcessMesh(Mesh& mData, aiMesh* mesh_, const aiScene* scene_)
{
	glm::vec3 maxVec = glm::vec3(-9999999, -9999999, -9999999);
	glm::vec3 minVec = glm::vec3(9999999, 9999999, 9999999);

	for (GLuint i = 0; i < mesh_->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;
		// Positions
		vector.x = mesh_->mVertices[i].x;
		vector.y = mesh_->mVertices[i].y;
		vector.z = mesh_->mVertices[i].z;
		_CheckMinMaxValues(vector, minVec, maxVec);

		vertex.position = vector;
		// Normals
		if (mesh_->mNormals != NULL) {
			vector.x = mesh_->mNormals[i].x;
			vector.y = mesh_->mNormals[i].y;
			vector.z = mesh_->mNormals[i].z;
			vertex.normal = vector;
		}

		// Texture Coordinates
		if (mesh_->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh_->mTextureCoords[0][i].x;
			vec.y = mesh_->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else
			vertex.texCoords = glm::vec2(0.0f, 0.0f);

		mData.vertices_.push_back(vertex);
	}

	// Process indices
	for (GLuint i = 0; i < mesh_->mNumFaces; i++)
	{
		aiFace face = mesh_->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			mData.indices_.push_back(face.mIndices[j]);
	}

	mData.minValueVector = minVec;
	mData.maxValueVector = maxVec;
}


void ObjectLoader::__ProcessNode(Mesh& mData, aiNode* node_, const aiScene* scene_)
{
	if (node_->mNumMeshes == 1) {
		aiMesh* mesh = scene_->mMeshes[node_->mMeshes[0]];
		this->__ProcessMesh(mData, mesh, scene_);
	}
	else if (node_->mNumChildren == 1) {
		this->__ProcessNode(mData, node_->mChildren[0], scene_);
	}
	else {
		//Log_DEBUG("[Mesh.hpp]", "ProcessNode function", "Meshes count 0 or greater then 1");
	}
}

//////////////////////////////////////////////////////////////////////////////

RawModel ObjectLoader::LoadObject(const std::vector<Vertex>& vertices_,
	const std::vector<GLuint>& indices_)
{
	RawModel result;
	result.vaoId = __CreateVAO();
	result.vboId = __CreateVBO(vertices_);
	result.eboId = __BindIndices(indices_);
	result.length = indices_.size();
	__StoreDataInAttributeArray(0, 3, GL_FLOAT, sizeof(Vertex), 0);
	__StoreDataInAttributeArray(1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, normal));
	__StoreDataInAttributeArray(2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, texCoords));
	__UnbindVAO();
	return result;
}

RawModel ObjectLoader::LoadObject(GLfloat vertices_[], const int& verticesLen_,
	GLuint indices_[], int indicesLen_)
{
	RawModel result;
	result.vaoId = __CreateVAO();
	result.vboId = __CreateVBO(vertices_, verticesLen_);
	result.eboId = __BindIndices(indices_, indicesLen_);
	result.length = 36;

	__StoreDataInAttributeArray(0, 3, GL_FLOAT, 5 * sizeof(GLfloat), 0);
	__StoreDataInAttributeArray(2, 2, GL_FLOAT, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat));

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	__UnbindVAO();

	m_vbos.push_back(result.vboId);
	m_ebos.push_back(result.eboId);

	return result;
}

MeshModel ObjectLoader::LoadMesh(GLchar *path_)
{
	Mesh meshData;
	MeshModel mdl;

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path_, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("ERROR::ASSIMP:: %s\n", import.GetErrorString());
		return mdl;
	}

	this->__ProcessNode(meshData, scene->mRootNode, scene);

	RawModel rModel = LoadObject(meshData.vertices_, meshData.indices_);
	mdl.vaoId = rModel.vaoId;
	mdl.length = rModel.length;
	mdl.minVector = meshData.minValueVector;
	mdl.maxVector = meshData.maxValueVector;

	return mdl;
}

void ObjectLoader::CleanUp()
{
	for (auto vao : m_vaos)
		glDeleteVertexArrays(1, &vao);

	for (auto vbo : m_vbos)
		glDeleteBuffers(1, &vbo);

	for (auto ebo : m_ebos)
		glDeleteBuffers(1, &ebo);
}