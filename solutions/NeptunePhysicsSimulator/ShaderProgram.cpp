#include "ShaderProgram.h"

#include "FileManager.h"

#include <glm/gtc/type_ptr.hpp>

//PRIVATE
void ShaderProgram::__AddShader(const char * _fPath, const GLenum& _shaderHandle)
{
    m_shaderIdList.push_back(__LoadShader(_fPath, _shaderHandle));
}

void ShaderProgram::__SetupProgram()
{
    printf("[ShaderProgram] Creating program.\n");
    this->m_programId = glCreateProgram();

    for (size_t i = 0; i < m_shaderIdList.size(); i++)
        glAttachShader(this->m_programId, m_shaderIdList[i]);
    
    glLinkProgram(this->m_programId);
    glValidateProgram(this->m_programId);
    __ShaderSanityCheck(this->m_programId, true);

    printf("[ShaderProgram] Program compiled and prepared for usage.\n");
}

void ShaderProgram::__ShaderSanityCheck(const GLuint& _id, const bool& _isProgram)
{
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

GLuint ShaderProgram::__LoadShader(const char * _fPath, const GLenum& _shaderHandle)
{
    GLuint shaderId;

    shaderId = glCreateShader(_shaderHandle);

    std::string shaderCode = GetStringFromFile(_fPath);

    char const * sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, NULL);
    glCompileShader(shaderId);

    __ShaderSanityCheck(shaderId, false);

    return shaderId;
}

//PROTECTED
GLint ShaderProgram::getUniformLocation(GLchar *value_)
{
    return glGetUniformLocation(this->m_programId, value_);
}

void ShaderProgram::LoadFloat(GLuint location_, float value_)
{
    glUniform1f(location_, value_);
}

void ShaderProgram::LoadVector3f(GLuint location_, glm::vec3 value_)
{
    glUniform3fv(location_, 1, glm::value_ptr(value_));
}

void ShaderProgram::LoadMatrix4f(GLuint location_, const glm::mat4 & value_)
{
    glUniformMatrix4fv(location_, 1, GL_FALSE, glm::value_ptr(value_));
}

void ShaderProgram::LoadMatrix4f(GLuint location_, NeptunePhysics::npMatrix4 value_)
{
    glUniformMatrix4fv(location_, 1, GL_FALSE, value_.m);
}

//PUBLIC
void ShaderProgram::Use()
{
    glUseProgram(this->m_programId);
}

void ShaderProgram::Stop()
{
    glUseProgram(0);
}

void ShaderProgram::CleanUp()
{
    Stop();
    for (size_t i = 0; i < m_shaderIdList.size(); i++)
    {
        glDetachShader(this->m_programId, m_shaderIdList[i]);
        glDeleteShader(m_shaderIdList[i]);
    }

    glDeleteProgram(this->m_programId);
}

ShaderProgram::ShaderProgram(const char * _vertShdrPath, const char * _fragShdrPath)
{
    __AddShader(_vertShdrPath, GL_VERTEX_SHADER);
    __AddShader(_fragShdrPath, GL_FRAGMENT_SHADER);
    __SetupProgram();
}