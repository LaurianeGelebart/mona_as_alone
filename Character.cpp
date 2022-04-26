#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "basics.h"
#include "Character.h"
    

void Character::set_current_pos(Position current_pos)
{
    this->current_pos = current_pos;
}

void Character::move(int dx, int dy)
{
    this->current_pos.x+=dx;
    this->current_pos.y+=dy;
}

void Character::draw_character(int filled)
{
    if(filled) 
    {
        glBegin(GL_QUADS);
    }
    else 
    {
        glBegin(GL_LINE_LOOP);
    }
    //glTexCoord2f(0.,0.);
    glVertex2f( this->current_pos.x-0.5*this->width, this->current_pos.y+0.5*this->height);
    //glTexCoord2f(1.,0.);
    glVertex2f( this->current_pos.x+0.5*this->width, this->current_pos.y+0.5*this->height);
    //glTexCoord2f(1.,1.);
    glVertex2f( this->current_pos.x+0.5*this->width, this->current_pos.y-0.5*this->height);
    //glTexCoord2f(0.,1.);
    glVertex2f( this->current_pos.x-0.5*this->width, this->current_pos.y-0.5*this->height);
    
    
    glColor3f(this->color.r, this->color.g, this->color.b);

    glEnd(); 
}

void Character::init_Character(int height, int width, Position pos, Position final_pos)
{
    this->height = height;
    this->width = width;
    this->start_pos.x = pos.x;
    this->start_pos.y=pos.y;
    this->current_pos.x= pos.x;
    this->current_pos.y= pos.y;
    this->end_pos.x = final_pos.x;
    this->end_pos.y = final_pos.y;
    this->color.r = 0.8 ; 
    this->color.g = 0.1 ; 
    this->color.b = 0.5 ; 
}
