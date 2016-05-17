#ifndef SHADER_H
#define SHADER_H

#include "math/npMatrix4.hpp"

// OpenGL
#include <GL/glew.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class ShaderProgram
{
public:
    ShaderProgram(const char * _vertShdrPath, const char * _fragShdrPath);
    ~ShaderProgram() {};

    void Use();
    void Stop();
    void CleanUp();

    GLuint getProgramID() { return m_programId; }

protected:
    GLint getUniformLocation(GLchar *value_);

    void LoadFloat(GLuint location_, float value_);
    void LoadVector3f(GLuint location_, glm::vec3 value_);
    void LoadMatrix4f(GLuint location_, glm::mat4 value_);

    void LoadMatrix4f(GLuint location_, NeptunePhysics::npMatrix4 value_);

private:
    GLuint m_programId;
    std::vector<GLuint> m_shaderIdList;

    /** AddShader
    Adds shader to the existing list of shaders and recompiles the shader program

    @param _fPath Path to shader file
    @param _shaderHandle Type of shader
    */
    void __AddShader(const char * _fPath, const GLenum& _shaderHandle);

    /** SetupProgram
    Links all the added shaders to the main program
    */
    void __SetupProgram();

    void __ShaderSanityCheck(const GLuint& _id, const bool& _isProgram);

    GLuint __LoadShader(const char * _fPath, const GLenum& _shaderHandle);

};
#endif