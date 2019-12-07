#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define SCREEN_W 800
#define SCREEN_H 480
#define SCREEN_FPS 60

typedef struct {
	GLfloat x;
	GLfloat y;
} Pos2d;

typedef struct {
	Pos2d position;
	Pos2d texcoord;
} VertexData2D;

/*
typedef struct {
	Pos2d vertices[4];
	GLuint indices[4];
	GLuint vbo; // = 0;
	GLuint ibo; // = 0;
} State;
*/

//Quad vertices
Pos2d quadVertices[4];
//Vertex indices
GLuint vertexIndices[4];
//Vertex buffer
GLuint vertexBuffer = 0;
//Index buffer
GLuint indexBuffer = 0;

GLuint textureID = 0;
void* pixels = NULL;
GLuint imageWidth = 0;
GLuint imageHeight = 0;
GLuint textureWidth = 0;
GLuint textureHeight = 0;


GLuint powerOf2(GLuint num) {
	if(num != 0) {
		num--;
		num |= (num >>  1);
		num |= (num >>  2);
		num |= (num >>  4);
		num |= (num >>  8);
		num |= (num >> 16);
		num++;
	}
	return num;
}

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

void freeTexture() {
	if(textureID != 0) {
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}
	if(pixels != NULL) {
		free(pixels);
		pixels = NULL;
	}
	imageWidth = 0;
	imageHeight = 0;
	textureWidth = 0;
	textureHeight = 0;
}

void initVBO() {
	if(textureID != 0 && vertexBuffer == 0) {
		VertexData2D vdata[4];
		GLuint idata[4];
		idata[0] = 0;
		idata[1] = 1;
		idata[2] = 2;
		idata[3] = 3;
		//create vbo
		glGenBuffersARB(1, &vertexBuffer);
		glBindBufferARB(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferDataARB(GL_ARRAY_BUFFER, 4*sizeof(VertexData2D), vdata, GL_DYNAMIC_DRAW);
		//create ibo
		glGenBuffersARB(1, &indexBuffer);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), idata, GL_DYNAMIC_DRAW);
		//unbind
		glBindBufferARB(GL_ARRAY_BUFFER, 0);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

bool loadTexFromPixels32(GLuint* pixels, GLuint imgw, GLuint imgh, GLuint texw, GLuint texh) {
	freeTexture();  //if it exists
	imageWidth = imgw;
	imageHeight = imgh;
	textureWidth = texw;
	textureHeight = texh;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0); // NULL
	GLenum err = glGetError();
	if(err != GL_NO_ERROR) {
		printf("OpenGL error:  %s\n", gluErrorString(err));
		return false;
	}
	initVBO();
	return true;
}

bool loadMedia() {
	/*
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
	*/

	bool texLoaded = false;
	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);
	ILboolean success = ilLoadImage("opengl.png");
	if(success == IL_TRUE) {
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if(success == IL_TRUE) {
			GLuint imgw = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
			GLuint imgh = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);
			GLuint texw = powerOf2(imgw);
			GLuint texh = powerOf2(imgh);
			if(imgw != texw || imgh != texh) {
				iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);
				iluEnlargeCanvas((int)texw, (int)texh, 1);
			}
			texLoaded = loadTexFromPixels32((GLuint*)ilGetData(), imgw, imgh, texw, texh);
		}
		ilDeleteImages(1, &imgID);
	}
	if(!texLoaded) printf("Unable to load opengl.png!\n");
	return texLoaded;
}

void update() {
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	/*
	glEnableClientState(GL_VERTEX_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexPointer(2, GL_FLOAT, 0, NULL);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
	*/
	glLoadIdentity();
	//texture.render((screen width - imgw) / 2, (screen height - imgh) / 2)
	if(textureID != 0) {
		// tex coordinates
		GLfloat ttop = 0.f;
		GLfloat tbottom = (GLfloat)imageHeight / (GLfloat) textureHeight;
		GLfloat tleft = 0.f;
		GLfloat tright = (GLfloat)imageWidth / (GLfloat) textureWidth;
		// vertex coordinates
		GLfloat qwidth = imageWidth;
		GLfloat qheight = imageHeight;
		// move to rendering point
		glTranslatef((SCREEN_W - imageWidth)/2, (SCREEN_H - imageHeight)/2, 0.f);
		//vertex data?
		VertexData2D vdata[4];
		//texture coordinates
		vdata[0].texcoord.x = tleft; vdata[0].texcoord.y = ttop;
		vdata[1].texcoord.x = tright; vdata[1].texcoord.y = ttop;
		vdata[2].texcoord.x = tright; vdata[2].texcoord.y = tbottom;
		vdata[3].texcoord.x = tleft; vdata[3].texcoord.y = tbottom;
		//vertex positions
		vdata[0].position.x = 0.f; vdata[0].position.y = 0.f;
		vdata[1].position.x = qwidth; vdata[1].position.y = 0.f;
		vdata[2].position.x = qwidth; vdata[2].position.y = qheight;
		vdata[3].position.x = 0.f; vdata[3].position.y = qheight;
		// set texture id
		glBindTexture(GL_TEXTURE_2D, textureID);
		glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glBindBufferARB(GL_ARRAY_BUFFER, vertexBuffer);
				glBufferSubDataARB(GL_ARRAY_BUFFER, 0, 4*sizeof(VertexData2D),vdata);
				glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, texcoord));
				glVertexPointer(2, GL_FLOAT, sizeof(VertexData2D), (GLvoid*)offsetof(VertexData2D, position));
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
				glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
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
