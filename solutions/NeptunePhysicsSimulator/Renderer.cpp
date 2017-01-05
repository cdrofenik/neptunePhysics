#include "Renderer.h"

void Renderer::PrepareForRendering()
{
    // Clear the colorbuffer
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(RawModel model_)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Draw mesh
    glBindVertexArray(model_.vaoId);
    glDrawElements(GL_TRIANGLES, model_.length, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::Render(MeshModel model_, bool wireFrameMode_)
{
    glPolygonMode(GL_FRONT_AND_BACK, wireFrameMode_ ? GL_LINE : GL_FILL);

    // Draw mesh
    glBindVertexArray(model_.vaoId);
        glEnableVertexAttribArray(0); // Position
        glEnableVertexAttribArray(1); // Normal
        glEnableVertexAttribArray(2); // Texture
        glDrawElements(GL_TRIANGLES, model_.length, GL_UNSIGNED_INT, 0);
        glDisableVertexArrayAttrib(model_.vaoId, 0);
        glDisableVertexArrayAttrib(model_.vaoId, 1);
        glDisableVertexArrayAttrib(model_.vaoId, 2);
    glBindVertexArray(0);
}

void Renderer::Render(DrawableShape model_)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Draw mesh
    glBindVertexArray(model_.getVAO());
        glEnableVertexAttribArray(0); // Position
        glEnableVertexAttribArray(1); // Color
        glDrawElements(GL_TRIANGLES, model_.getVAOLength(), GL_UNSIGNED_INT, 0);
        glDisableVertexArrayAttrib(model_.getVAO(), 0);
        glDisableVertexArrayAttrib(model_.getVAO(), 1);
    glBindVertexArray(0);
}

void Renderer::RenderArrays(RawModel model_)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Draw mesh
    glBindVertexArray(model_.vaoId);
    glDrawArrays(GL_TRIANGLES, 0, model_.length);
    glBindVertexArray(0);
}

void Renderer::Render(GLuint vaoId_, int length_)
{
    // Draw mesh
    glBindVertexArray(vaoId_);
    glDrawElements(GL_TRIANGLES, length_, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}