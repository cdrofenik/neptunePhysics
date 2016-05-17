#include "TextureLoader.h"

//Library for loading images
#include "SOIL.h"

void TextureLoader::UseTexture(const GLuint& textureId_, const GLuint& shaderId_,
	const char *uniformId)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId_);
	glUniform1i(glGetUniformLocation(shaderId_, uniformId), 0);
}

GLuint TextureLoader::LoadTexture(const char *texturePath_)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(texturePath_, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_textures.push_back(texture);

	return texture;
}

void TextureLoader::CleanUp()
{
	//TODO glDeleteTextures()
	m_textures.clear();
}

TextureLoader::TextureLoader()
{

}

TextureLoader::~TextureLoader()
{
}
