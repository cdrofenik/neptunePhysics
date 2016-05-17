#ifndef MODELSHADER_H
#define MODELSHADER_H

#include "ShaderProgram.h"

class ModelShader : public ShaderProgram
{
public:
    ModelShader(const char * _vertShdrPath, const char * _fragShdrPath);
    ~ModelShader() {};

    void LoadModelMatrix(glm::mat4 matrix_);
    void LoadViewMatrix(glm::mat4 matrix_);
    void LoadProjectionMatrix(glm::mat4 matrix_);
    void LoadLightPosition(glm::vec3 vector_);
    void LoadLightColor(glm::vec3 color_);

    void LoadShineVariables(float damper_, float reflectivity_);
    void LoadModelMatrix(NeptunePhysics::npMatrix4 matrix_);

protected:
    void LoadAllUniforms();

private:
    //Uniform variables
    GLuint m_viewLocation;
    GLuint m_projectionLocation;
    GLuint m_modelLocation;
    GLuint m_lightPositionLocation;
    GLuint m_lightColorLocation;
    GLuint m_shineDamper;
    GLuint m_reflectivity;

};


#endif