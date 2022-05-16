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

void Character::move(float accx)
{
    this->speed.x = accx;
}

void Character::jump(float accy)
{
    this->speed.y = accy;
     printf("jump activé %f\n",this->speed.y);
}

void Character::set_position()
{
    this->current_pos.x += this->speed.x;

    this->current_pos.y += this->speed.y + this->acc.y;
    if(this->current_pos.y < 4.4)
    {
        this->current_pos.y = 5;
    }
    
     printf("pos %f\n",this->current_pos.y);
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

Character::Character (int height, int width, Position pos, Position final_pos)
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
    this->acc.x = 0;
    this->acc.y = -g;
    this->speed.x = 0;
    this->speed.y = 0;
}
