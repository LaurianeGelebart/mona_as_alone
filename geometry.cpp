#include "geometry.h"


void drawSquare(Square square) 
{
    glBegin(GL_QUADS);

    glColor3f(0.1, 0.2, 0.5);
    
    glVertex2f(square.pos_square.x-0.5*square.width,square.pos_square.y+0.5*square.height);
    glVertex2f(square.pos_square.x+0.5*square.width,square.pos_square.y+0.5*square.height);
    glVertex2f(square.pos_square.x+0.5*square.width,square.pos_square.y-0.5*square.height);
    glVertex2f(square.pos_square.x-0.5*square.width,square.pos_square.y-0.5*square.height);

    glEnd();
    
}