#include "ModelShader.h"

void ModelShader::LoadAllUniforms()
{
    m_viewLocation = getUniformLocation("view");
    m_projectionLocation = getUniformLocation("projection");
    m_modelLocation = getUniformLocation("model");
    m_lightPositionLocation = getUniformLocation("lightPosition");
    m_lightColorLocation = getUniformLocation("lightColour");
    //m_shineDamper = getUniformLocation("shineDamper");
   // m_reflectivity = getUniformLocation("reflectivity");
}

void ModelShader::LoadShineVariables(float damper_, float reflectivity_)
{
    //LoadFloat(m_shineDamper, damper_);
    //LoadFloat(m_reflectivity, reflectivity_);
}

void ModelShader::LoadModelMatrix(const glm::mat4 &matrix_)
{
    LoadMatrix4f(m_modelLocation, matrix_);
}

void ModelShader::LoadViewMatrix(const glm::mat4 &matrix_)
{
    LoadMatrix4f(m_viewLocation, matrix_);
}

void ModelShader::LoadProjectionMatrix(const glm::mat4 &matrix_)
{
    LoadMatrix4f(m_projectionLocation, matrix_);
}

void ModelShader::LoadLightPosition(glm::vec3 vector_)
{
    LoadVector3f(m_lightPositionLocation, vector_);
}

void ModelShader::LoadLightColor(glm::vec3 color_)
{
    LoadVector3f(m_lightColorLocation, color_);
}

void ModelShader::LoadModelMatrix(NeptunePhysics::npMatrix4 matrix_)
{
    LoadMatrix4f(m_modelLocation, matrix_);
}

ModelShader::ModelShader(const char * _vertShdrPath, const char * _fragShdrPath) :
    ShaderProgram(_vertShdrPath, _fragShdrPath)
{
    LoadAllUniforms();
}

