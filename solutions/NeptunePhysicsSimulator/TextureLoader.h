#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "ContainerHelper.hpp"

#include <GL\glew.h>
#include <vector>

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	GLuint LoadTexture(const char *texturePath_);

	void UseTexture(const GLuint& textureId_, const GLuint& shaderId_,
		const char *uniformId_);
	void CleanUp();

private:
	std::vector<GLuint> m_textures;
};

#endif