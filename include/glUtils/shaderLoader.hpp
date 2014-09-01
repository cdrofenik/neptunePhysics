#ifndef NEPTUNE_SHADERLOADER_H
#define NEPTUNE_SHADERLOADER_H

#include <GL/glew.h>
#include <vector>

#include "glfw3.h"

static std::vector<std::string> msgLogger;

/* Load vertex and fragment shaders */
GLuint Load2Shaders(const char * vertex_file_path, const char * fragment_file_path);

#endif