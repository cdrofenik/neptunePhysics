#include "glUtils/shaderLoader.hpp"

#include <fstream>
#include <streambuf>

std::string _getStringFromFile(const char * vertex_file_path)
{
	std::ifstream vertexIfStream(vertex_file_path);
	std::string vertexShaderString;

	if (!vertexIfStream)
	{
		msgLogger.push_back("Bad file read (probably file path mistake)...");
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
		msgLogger.push_back(&errorLog[0]);
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
	msgLogger.push_back("Reading vertex shader at " + *vertex_file_path);
	std::string vertShaderSrc = _getStringFromFile(vertex_file_path);
	char const * p_vertexSourcePointer = vertShaderSrc.c_str();
	msgLogger.push_back("Reading fragment shader at " + *fragment_file_path);
	std::string fragShaderSrc = _getStringFromFile(fragment_file_path);
	char const * p_fragSourcePointer = fragShaderSrc.c_str();

	//Compiling Vertex Shader
	msgLogger.push_back("Compiling fragment shader at " + *vertex_file_path);
	glShaderSource(vertexShaderID, 1, &p_vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	if (!_sanityCheck(vertexShaderID))
		return res;

	//Compiling Fragment Shader
	msgLogger.push_back("Compiling fragment shader at " + *fragment_file_path);
	glShaderSource(fragmentShaderID, 1, &p_fragSourcePointer, NULL);
	glCompileShader(fragmentShaderID);
	
	if (!_sanityCheck(fragmentShaderID))
		return res;

	//Main shader program
	msgLogger.push_back("Linking main program... ");
	GLuint ProgramID;
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertexShaderID);
	glAttachShader(ProgramID, fragmentShaderID);
	glLinkProgram(ProgramID);

	if (!_sanityCheck(ProgramID))
		return res;

	msgLogger.push_back("Cleaning up shaders... ");
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return ProgramID;
}