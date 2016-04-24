
#include "OpenGLComponent.h"
#include "ShaderComponent.hpp"
#include "CameraComponent.hpp"

#include "DrawableObject.h"

#include <vector>

class ParticleSimulator
{
public:
	ParticleSimulator();
	~ParticleSimulator();

	void initialize();
	void execute();

private:
	OpenGLComponent* window;
	ShaderComponent shader;
	CameraComponent camera;

	//Create Manager struct as container for data
	std::vector<DrawableObject> drawableList;

};