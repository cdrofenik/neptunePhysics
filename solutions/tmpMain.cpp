#include <iostream>
using namespace std;

#include "vgl.h"
#include "LoadShaders.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][2] = {
			{ -0.70, -0.70 }, // Triangle 1
			{ 0.65, -0.70 },
			{ -0.70, 0.65 },
			{ 0.70, -0.65 }, // Triangle 2
			{ 0.70, 0.70 },
			{ -0.65, 0.70 }
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
	glUseProgram(program);

	//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

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
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);

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