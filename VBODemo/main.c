#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SCREEN_W 800
#define SCREEN_H 480
#define SCREEN_FPS 60

typedef struct {
	GLfloat x;
	GLfloat y;
} Pos2d;

typedef struct {
	Pos2d vertices[4];
	GLuint indices[4];
	GLuint vbo; // = 0;
	GLuint ibo; // = 0;
} State;

//Quad vertices
Pos2d quadVertices[4];
//Vertex indices
GLuint vertexIndices[4];
//Vertex buffer
GLuint vertexBuffer = 0;
//Index buffer
GLuint indexBuffer = 0;



bool initGL() {
	GLenum glewError = glewInit();
	if(glewError != GLEW_OK) return false;
	if(!GLEW_VERSION_1_4) return false;
	glViewport(0.f, 0.f, SCREEN_W, SCREEN_H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_W, SCREEN_H, 0.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLenum err = glGetError();
	if(err != GL_NO_ERROR) {
		printf("OpenGL error:  %s\n", gluErrorString(err));
		return false;
	}
	ilInit();
	iluInit();
	ilClearColour(0xFF,0xFF,0xFF,0x00);
	ILenum ilErr = ilGetError();
	if(ilErr != IL_NO_ERROR) {
		printf("DevIL error:  %s\n", iluErrorString(ilErr));
		return false;
	}
	return true;
}

bool loadMedia() {
	quadVertices[0].x = SCREEN_W * 1.f / 4.f;
	quadVertices[0].y = SCREEN_H * 1.f / 4.f;
	quadVertices[1].x = SCREEN_W * 3.f / 4.f;
	quadVertices[1].y = SCREEN_H * 1.f / 4.f;
	quadVertices[2].x = SCREEN_W * 3.f / 4.f;
	quadVertices[2].y = SCREEN_H * 3.f / 4.f;
	quadVertices[3].x = SCREEN_W * 1.f / 4.f;
	quadVertices[3].y = SCREEN_H * 3.f / 4.f;
	vertexIndices[0] = 0;
	vertexIndices[1] = 1;
	vertexIndices[2] = 2;
	vertexIndices[3] = 3;

	//VBO
	glGenBuffersARB(1, &vertexBuffer);
	glBindBufferARB(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferDataARB(GL_ARRAY_BUFFER, 4*sizeof(Pos2d), quadVertices, GL_STATIC_DRAW);

	//IBO
	glGenBuffersARB(1, &indexBuffer);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), vertexIndices, GL_STATIC_DRAW);

	return true;
}

void update() {
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexPointer(2, GL_FLOAT, 0, NULL);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
	glutSwapBuffers();
}

void runMainLoop(int val) {
	update();
	render();
	glutTimerFunc(1000/SCREEN_FPS, runMainLoop, val);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitContextVersion(1, 4);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_W, SCREEN_H);
	glutCreateWindow("VBODemo");
	if(!initGL()) {
		printf("Unable to create window!\n");
		return -1;
	}

	if(!loadMedia()) {
		printf("Unable to load media!\n");
		return -2;
	}

	glutDisplayFunc(render);
	glutTimerFunc(1000/SCREEN_FPS, runMainLoop, 0);
	glutMainLoop();

	return 0;
}
