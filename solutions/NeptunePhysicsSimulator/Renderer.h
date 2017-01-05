#ifndef RENDERER_H
#define RENDERER_H

#include "ContainerHelper.hpp"
#include "DrawableBV.h"

class Renderer
{
public:
	Renderer() {}
	~Renderer() {}

	void PrepareForRendering();
	void Render(RawModel model_);
	void Render(MeshModel model_, bool wireFrameMode_);
	void Render(DrawableShape model_);
	void RenderArrays(RawModel model_);
	void Render(GLuint vaoId_, int length_);

};

#endif