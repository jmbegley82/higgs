#include "LUtil.h"

int gColorMode = COLOR_MODE_CYAN;
GLfloat gProjectionScale = 1.f;

bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void update() {
}

void render() {
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    //Reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Move to center of screen
    glTranslatef( SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f );

    //Render quad
/*
    glBegin( GL_QUADS );
        glVertex2f( -0.5f, -0.5f );
        glVertex2f(  0.5f, -0.5f );
        glVertex2f(  0.5f,  0.5f );
        glVertex2f( -0.5f,  0.5f );
    glEnd();
*/
    if(gColorMode == COLOR_MODE_CYAN) {
	    // RGBK
	    glBegin(GL_QUADS);
	    glColor4f(0.f, 1.f, 0.f, 1.f); glVertex2f(-200.f, -200.f);
	    glColor4f(1.f, 0.f, 0.f, 1.f); glVertex2f( 200.f, -200.f);
	    glColor4f(0.f, 0.f, 1.f, 1.f); glVertex2f( 200.f,  200.f);
	    glColor4f(0.f, 0.f, 0.f, 1.f); glVertex2f(-200.f,  200.f);
	    glEnd();
	    //gColorMode = COLOR_MODE_MULTI;
    } else {
	    // "CMY"K
	    glBegin(GL_QUADS);
	    glColor4f(1.f, 1.f, 0.f, 1.f); glVertex2f(-200.f, -200.f);
	    glColor4f(1.f, 0.f, 1.f, 1.f); glVertex2f( 200.f, -200.f);
	    glColor4f(0.f, 1.f, 1.f, 1.f); glVertex2f( 200.f,  200.f);
	    glColor4f(0.f, 0.f, 0.f, 1.f); glVertex2f(-200.f,  200.f);
	    glEnd();
	    //gColorMode = COLOR_MODE_CYAN;
    }
    //Update screen
    glutSwapBuffers();
}

void runMainLoop( int val )
{
    //Frame logic
    update();
    render();

    //Run frame one more time
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );
}

void handleKeys( unsigned char key, int x, int y )
{
    //If the user presses q
    if( key == 'q' )
    {
        //Toggle color mode
        if( gColorMode == COLOR_MODE_CYAN )
        {
            gColorMode = COLOR_MODE_MULTI;
        }
        else
        {
            gColorMode = COLOR_MODE_CYAN;
        }
    }
    else if( key == 'e' )
    {
        //Cycle through projection scales
        if( gProjectionScale == 1.f )
        {
            //Zoom out
            gProjectionScale = 2.f;
        }
        else if( gProjectionScale == 2.f )
        {
            //Zoom in
            gProjectionScale = 0.5f;
        }
        else if( gProjectionScale == 0.5f )
        {
            //Regular zoom
            gProjectionScale = 1.f;
        }

        //Update projection matrix
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0.0, SCREEN_WIDTH * gProjectionScale, SCREEN_HEIGHT * gProjectionScale, 0.0, 1.0, -1.0 );
    }
}
