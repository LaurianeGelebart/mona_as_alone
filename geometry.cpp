#include "geometry.h"


void drawSquare(Square square) 
{
    /*glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,this->textID);*/
        glBegin(GL_QUADS);
        glTexCoord2f(0.,0.);
        glVertex2f(square.pos_square.x-0.5*square.width,square.pos_square.y+0.5*square.height);
        glTexCoord2f(1.,0.);
        glVertex2f(square.pos_square.x+0.5*square.width,square.pos_square.y+0.5*square.height);
        glTexCoord2f(1.,1.);
        glVertex2f(square.pos_square.x+0.5*square.width,square.pos_square.y-0.5*square.height);
        glTexCoord2f(0.,1.);
        glVertex2f(square.pos_square.x-0.5*square.width,square.pos_square.y-0.5*square.height);
        glColor3f(0.1, 0.2, 0.5);
        glEnd();
    /*glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);*/    
}