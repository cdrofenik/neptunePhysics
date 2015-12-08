#include "mesh.h"

#include <cstdio>
#include <assert.h>

void Mesh::initMesh()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
		&this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
		&this->indices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}


void Mesh::clear() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);

	this->vertices.clear();
	this->indices.clear();
	this->textures.clear();
}

void Mesh::Draw(Shader _shader) {

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}




void Mesh::initMesh() {

	// Generate and populate the buffers with vertex attributes and the indices
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapes[0].mesh.positions[0]) * shapes[0].mesh.positions.size(), &shapes[0].mesh.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION_LOCATION);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Settings up texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapes[0].mesh.texcoords[0]) * shapes[0].mesh.texcoords.size(), &shapes[0].mesh.texcoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEX_COORD_LOCATION);
	glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Settings up normals
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapes[0].mesh.normals[0]) * shapes[0].mesh.normals.size(), &shapes[0].mesh.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL_LOCATION);
	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Settings up indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapes[0].mesh.indices[0]) * shapes[0].mesh.indices.size(), &shapes[0].mesh.indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[WVP_MAT_VB]);

	for (unsigned int i = 0; i < 4; i++) {
		glEnableVertexAttribArray(WVP_LOCATION + i);
		glVertexAttribPointer(WVP_LOCATION + i, 4, GL_FLOAT, GL_FALSE, sizeof(npMatrix4), (const GLvoid*)(sizeof(GLfloat) * i * 4));
		glVertexAttribDivisor(WVP_LOCATION + i, 1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[WORLD_MAT_VB]);

	for (unsigned int i = 0; i < 4; i++) {
		glEnableVertexAttribArray(WORLD_LOCATION + i);
		glVertexAttribPointer(WORLD_LOCATION + i, 4, GL_FLOAT, GL_FALSE, sizeof(npMatrix4), (const GLvoid*)(sizeof(GLfloat) * i * 4));
		glVertexAttribDivisor(WORLD_LOCATION + i, 1);
	}

	NumIndices = shapes[0].mesh.positions.size();
}

void Mesh::clear() {
	//TODO clear container(s)
	shapes.clear();
	materials.clear();
}

bool Mesh::loadMesh(const std::string& _filename)
{
	/* Release the previously loaded mesh (if it exists) */
	clear();

	bool Ret = false;

	std::string err = tinyobj::LoadObj(shapes, materials, _filename.c_str());

	if (!err.empty()) {
		printf("Error: %s\n", err);
		//exit(1);
	}

	printf("# of shapes    : %d\n", shapes.size());
	printf("# of positions for shape    : %d\n", shapes[0].mesh.positions.size());
	printf("# of texcoord for shape    : %d\n", shapes[0].mesh.texcoords.size());
	printf("# of normals for shape    : %d\n", shapes[0].mesh.normals.size());
	printf("# of indices   : %d\n", shapes[0].mesh.indices.size());
	printf("# of materials : %d\n", materials.size());

	/*for (size_t i = 0; i < shapes.size(); i++) {
		printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
		printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
		printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
		assert((shapes[i].mesh.indices.size() % 3) == 0);
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
			printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3 * f + 0], shapes[i].mesh.indices[3 * f + 1], shapes[i].mesh.indices[3 * f + 2], shapes[i].mesh.material_ids[f]);
		}

		printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
		assert((shapes[i].mesh.positions.size() % 3) == 0);
		for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
			printf("  v[%ld] = (%f, %f, %f)\n", v,
				shapes[i].mesh.positions[3 * v + 0],
				shapes[i].mesh.positions[3 * v + 1],
				shapes[i].mesh.positions[3 * v + 2]);
		}
	}*/
	//for (size_t i = 0; i < materials.size(); i++) {
	//	printf("material[%ld].name = %s\n", i, materials[i].name.c_str());
	//	printf("  material.Ka = (%f, %f ,%f)\n", materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]);
	//	printf("  material.Kd = (%f, %f ,%f)\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
	//	printf("  material.Ks = (%f, %f ,%f)\n", materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]);
	//	printf("  material.Tr = (%f, %f ,%f)\n", materials[i].transmittance[0], materials[i].transmittance[1], materials[i].transmittance[2]);
	//	printf("  material.Ke = (%f, %f ,%f)\n", materials[i].emission[0], materials[i].emission[1], materials[i].emission[2]);
	//	printf("  material.Ns = %f\n", materials[i].shininess);
	//	printf("  material.Ni = %f\n", materials[i].ior);
	//	printf("  material.dissolve = %f\n", materials[i].dissolve);
	//	printf("  material.illum = %d\n", materials[i].illum);
	//	printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
	//	printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
	//	printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
	//	//printf("  material.map_Ns = %s\n", materials[i].normal_texname.c_str());
	//	std::map<std::string, std::string>::const_iterator it(materials[i].unknown_parameter.begin());
	//	std::map<std::string, std::string>::const_iterator itEnd(materials[i].unknown_parameter.end());
	//	for (; it != itEnd; it++) {
	//		printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
	//	}
	//	printf("\n");
	//}

	initMesh();

	return Ret;
}

void Mesh::render(unsigned int NumInstances, const npMatrix4* WVPMats, const npMatrix4* WorldMats) {

	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[WVP_MAT_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(npMatrix4) * NumInstances, WVPMats, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[WORLD_MAT_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(npMatrix4) * NumInstances, WorldMats, GL_DYNAMIC_DRAW);

	glBindVertexArray(m_VAO);

	glDrawElementsInstancedBaseVertex(GL_TRIANGLES,
		NumIndices,
		GL_UNSIGNED_INT,
		(void*)(sizeof(unsigned int) * shapes[0].mesh.indices[0]),
		NumInstances,
		shapes[0].mesh.indices[0]);

	// Make sure the VAO is not changed from the outside 
	glBindVertexArray(0);
}