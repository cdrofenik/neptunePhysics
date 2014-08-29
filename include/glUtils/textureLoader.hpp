#ifndef NEPTUNE_SHADERLOADER_H
#define NEPTUNE_SHADERLOADER_H

#include "glfw3.h"

/* Load DDS with GLEWs loader */
GLuint LoadDDS(const char * vertex_file_path, const char * fragment_file_path);

#endif