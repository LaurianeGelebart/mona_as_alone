#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "basics.h"

void onWindowResized(unsigned int width, unsigned int height)
{ 
    float aspectRatio = width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1) 
    {
        gluOrtho2D(
        0, GL_VIEW_SIZE * aspectRatio, 
        0, GL_VIEW_SIZE);
    }
    else
    {
        gluOrtho2D(
        0, GL_VIEW_SIZE,
        0, GL_VIEW_SIZE / aspectRatio);
    }
}


/* Objets cannoniques */
void drawOrigin() 
{
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 1.0 , 0.0);

    glColor3f(0., 1., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 0.0 , 1.0);

    glEnd();

    glColor3fv(currentColor);
}

void drawSquare(int filled,float width, float height, float x, float y) 
{
    if(filled) 
    {
        glBegin(GL_QUADS);
    }
    else 
    {
        glBegin(GL_LINE_LOOP);
    }

    glVertex2f(x-0.5*width,y+0.5*height);
    glVertex2f(x+0.5*width,y+0.5*height);
    glVertex2f(x+0.5*width,y-0.5*height);
    glVertex2f(x-0.5*width,y-0.5*height);
    
    glColor3f(0.1, 0.2, 0.5);

    glEnd();
    
}
