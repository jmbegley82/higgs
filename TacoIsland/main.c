#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_FPS 60

GLuint tex   = 0;
GLuint tex_w = 0;
GLuint tex_h = 0;

bool initGL() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glEnable(GL_TEXTURE_2D);
	GLenum error = glGetError();
	if(error != GL_NO_ERROR) {
		printf("OpenGL error: %s\n", gluErrorString(error));
		return false;
	}
	return true;
}

GLuint* getCheckerboard() {
	GLuint* retval = NULL;
	const int cbWidth = 128;
	const int cbHeight = 128;
	const int cbPixels = cbWidth * cbHeight;

	retval = malloc(sizeof(GLuint)*cbPixels);
	for(int i=0; i<cbPixels; ++i) {
		GLubyte* pixel = (GLubyte*)&retval[i];
		if(i/128&16^i%128&16) {
			pixel[0] = 0xFF;
			pixel[1] = 0xFF;
			pixel[2] = 0xFF;
		} else {
			pixel[0] = 0xFF;
			pixel[1] = 0x00;
			pixel[2] = 0x00;
		}
		pixel[3] = 0xFF;
	}

	return retval;
}

GLuint getCBTexture() {
	GLuint retval = 0;
	GLuint* cb = getCheckerboard();
	assert(cb != NULL);
	glGenTextures(1, &retval);
	glBindTexture(GL_TEXTURE_2D, retval);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, cb);
	free(cb);	//iffy part 1
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, NULL);
	GLenum error = glGetError();
	if(error != GL_NO_ERROR) {
		printf("OpenGL error:  %s\n", gluErrorString(error));
		return 0;
	}
	return retval;
}

void update() {
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(SCREEN_WIDTH/2.f, SCREEN_HEIGHT/2.f, 0.f);
	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
	/*
	glColor3f(1.f, 1.f, 0.f); glVertex2f(-0.25f * SCREEN_WIDTH, -0.25f * SCREEN_HEIGHT);
	glColor3f(0.f, 1.f, 1.f); glVertex2f( 0.25f * SCREEN_WIDTH, -0.25f * SCREEN_HEIGHT);
	glColor3f(1.f, 0.f, 1.f); glVertex2f( 0.25f * SCREEN_WIDTH,  0.25f * SCREEN_HEIGHT);
	glColor3f(0.f, 0.f, 0.f); glVertex2f(-0.25f * SCREEN_WIDTH,  0.25f * SCREEN_HEIGHT);
	*/
	glTexCoord2f(0.f, 0.f); glVertex2f(-200.f, -200.f);
	glTexCoord2f(1.f, 0.f); glVertex2f( 200.f, -200.f);
	glTexCoord2f(1.f, 1.f); glVertex2f( 200.f,  200.f);
	glTexCoord2f(0.f, 1.f); glVertex2f(-200.f,  200.f);
	glEnd();
	glutSwapBuffers();
}

void runMainLoop(int val) {
	update();
	render();
	glutTimerFunc(1000/SCREEN_FPS, runMainLoop, val);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitContextVersion(2, 1);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("TacoIsland");
	if(!initGL()) {
		printf("Unable to initialize OpenGL\n");
		return -1;
	}

	tex = getCBTexture();
	
	//glutKeyboardFunction(handleKeys);
	glutDisplayFunc(render);

	glutTimerFunc(1000/SCREEN_FPS, runMainLoop, 0);
	glutMainLoop();
	return 0;
}
