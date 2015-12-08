#include "Shader.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

//TODO: Make this class a header file implementation

Shader::Shader()
{
	shaderIdList = std::vector<GLuint>();
}

Shader::~Shader()
{
	shaderIdList.clear();
	glDeleteProgram(programId);
}

std::string Shader::GetStringFromFile(const char * _fPath) {
	std::string fileString;
	std::ifstream fileStream(_fPath, std::ios::in);

	if (fileStream.is_open()){
		std::string Line = "";
		while (getline(fileStream, Line))
			fileString += "\n" + Line;
		fileStream.close();
	}
	else{
		printf("Impossible to open %s. Are you in the right directory?\n", _fPath);
		getchar();
		return 0;
	}

	return fileString;
}

void Shader::ShaderSanityCheck(const GLuint& _id, const bool& _isProgram) {
	GLint success = GL_FALSE;
	GLchar infoLog[512];

	if (_isProgram) {
		glGetProgramiv(_id, GL_LINK_STATUS, &success);
		if (!success){
			glGetProgramInfoLog(_id, 512, NULL, infoLog);
			printf("[Shader] %s\n", infoLog);
		}
	}
	else {
		glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(_id, 512, NULL, infoLog);
			printf("[Shader] %s\n", infoLog);
		}
	}
}

GLuint Shader::LoadShader(const char * _fPath, const ShaderType& _shaderHandle) {
	GLuint shaderId;

	switch (_shaderHandle) {
	case ShaderType::VERTEX_SHADER:
		shaderId = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::FRAGMENT_SHADER:
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	std::string shaderCode = GetStringFromFile(_fPath);

	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	glCompileShader(shaderId);

	ShaderSanityCheck(shaderId, false);

	return shaderId;
}

void Shader::AddShader(const char * _fPath, const ShaderType& _shaderHandle) {
	shaderIdList.push_back(LoadShader(_fPath, _shaderHandle));
}

void Shader::SetupProgram() {

	printf("[Shader] Creating program.\n");
	this->programId = glCreateProgram();

	for (size_t i = 0; i < shaderIdList.size(); i++)
		glAttachShader(this->programId, shaderIdList[i]);

	glLinkProgram(this->programId);
	ShaderSanityCheck(this->programId, true);

	for (size_t i = 0; i < shaderIdList.size(); i++)
		glDeleteShader(shaderIdList[i]);

	shaderIdList.clear();

	printf("[Shader] Program compiled and cleaned up.\n");
}

void Shader::Use() {
	glUseProgram(this->programId);
}