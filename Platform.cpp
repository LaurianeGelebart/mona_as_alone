#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "basics.h"
#include "Platform.h"

void Platform::draw_platform(int filled,float width, float height, float x, float y) 
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