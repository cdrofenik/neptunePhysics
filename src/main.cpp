#include <iostream>
using namespace std;

#include "vgl.h"
#include "LoadShaders.h"

#include "glm/gtc/matrix_transform.hpp"


enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 3;

void init(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][3] = {
			{ -0.10, 0.00, 0.0 }, // Triangle 1
			{ 0.10, 0.00, 0.0 },
			{ 0.00, 0.50, 0.0 }
			//{ 0.00, 0.10, 0.05 }, // Triangle 2
			//{ 0.00, -0.10, 0.05 },
			//{ 0.50, 0.00, 0.05 }
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "../external/shaders/basic/triangles.vert" },
			{ GL_FRAGMENT_SHADER, "../external/shaders/basic/triangles.frag" },
			{ GL_NONE, NULL },
	};

	GLuint program = LoadShaders(shaders);

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(program, "MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
	
	glUseProgram(program);

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(512, 386);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Ballistic"); //argv[0]);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}

	//Set default background colour
	glClearColor(1, 1, 1, 1);

	init();

	glutDisplayFunc(display);

	glutMainLoop();
}