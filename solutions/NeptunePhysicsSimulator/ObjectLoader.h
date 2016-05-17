#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include "ContainerHelper.hpp"

// ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <GL\glew.h>

#include <vector>

class ObjectLoader
{
public:
    ObjectLoader();
    ~ObjectLoader();

    MeshModel LoadMesh(GLchar *path_);

    RawModel LoadObject(const std::vector<Vertex>& verticesData_,
                        const std::vector<GLuint>& indiciesData_);

    RawModel LoadObject(GLfloat vertices_[], const int& verticesLen_,
                        GLuint indices_[], int indicesLen_);

    void CleanUp();

private:
    std::vector<GLuint> m_vaos;
    std::vector<GLuint> m_vbos;
    std::vector<GLuint> m_ebos;

    GLuint __CreateVAO();

    GLuint __CreateVBO(std::vector<Vertex> verticesData_);
    GLuint __BindIndices(std::vector<GLuint> indiciesData_);

    GLuint __CreateVBO(GLfloat data_[], const int& dataSize_);
    GLuint __BindIndices(GLuint data_[], const int& dataSize_);

    void __StoreDataInAttributeArray(const int& attribNumber_, const int& elementCount_,
        const GLenum& elementType_, const int& elementLength_, const int& startPos_);
    
    void __ProcessNode(Mesh& mData_, aiNode* node_, const aiScene* scene_);
    void __ProcessMesh(Mesh& mData_, aiMesh* mesh_, const aiScene* scene_);
    
    void __UnbindVAO();

};

#endif