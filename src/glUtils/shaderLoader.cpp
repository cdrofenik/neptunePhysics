#include "glUtils/shaderLoader.hpp"

#include <fstream>
#include <streambuf>

std::string _getStringFromFile(const char * vertex_file_path)
{
	std::ifstream vertexIfStream(vertex_file_path);
	std::string vertexShaderString;

	if (!vertexIfStream)
	{
		printf("Bad file read (probably file path mistake)...\n");
		return "";
	}

	vertexIfStream.seekg(0, std::ios::end);
	vertexShaderString.reserve(vertexIfStream.tellg());
	vertexIfStream.seekg(0, std::ios::beg);

	vertexShaderString.assign((std::istreambuf_iterator<char>(vertexIfStream)), std::istreambuf_iterator<char>());

	return vertexShaderString;
}

bool _sanityCheck(GLuint& shader)
{
	GLint isCompiled = 0;
	int logLength;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorLog(logLength + 1); //The maxLength includes the NULL character
		glGetShaderInfoLog(shader, logLength, &logLength, &errorLog[0]);
		//Logger::addToLogger("Bad file read (probably file path mistake)..." + errorLog[0]);
	}

	return true;
}

GLuint Load2Shaders(const char * vertex_file_path, const char * fragment_file_path)
{
	GLuint vertexShaderID, fragmentShaderID;

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint res = GL_FALSE;

	//Vertex Shader
	printf("Reading vertex shader at %s \n", vertex_file_path);
	std::string vertShaderSrc = _getStringFromFile(vertex_file_path);
	char const * p_vertexSourcePointer = vertShaderSrc.c_str();

	printf("Reading fragment shader at %s \n", fragment_file_path);
	std::string fragShaderSrc = _getStringFromFile(fragment_file_path);
	char const * p_fragSourcePointer = fragShaderSrc.c_str();

	//Compiling Vertex Shader
	printf("Compiling vertex shader at %s \n", vertex_file_path);
	glShaderSource(vertexShaderID, 1, &p_vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	if (!_sanityCheck(vertexShaderID))
		return res;

	//Compiling Fragment Shader
	printf("Compiling fragment shader at %s \n", fragment_file_path);
	glShaderSource(fragmentShaderID, 1, &p_fragSourcePointer, NULL);
	glCompileShader(fragmentShaderID);
	
	if (!_sanityCheck(fragmentShaderID))
		return res;

	//Main shader program
	printf("Linking main program...\n");
	GLuint ProgramID;
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertexShaderID);
	glAttachShader(ProgramID, fragmentShaderID);
	glLinkProgram(ProgramID);

	if (!_sanityCheck(ProgramID))
		return res;

	printf("Cleaning up shaders... \n");
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return ProgramID;
}