#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "constants.h"
#include "geometry.h"
#include "color.h"
#include "Character.h"
    

Character::Character (int height, int width, Position pos, Position final_pos)
{
    this->height = height;
    this->width = width;
    this->start_pos = pos;
    this->current_pos = pos;
    this->end_pos = final_pos;
    this->color = {0.8, 0.1, 0.5} ;
    this->acc = {0, -g};
    this->speed = {0,0};
    this->keystate = SDL_GetKeyboardState(NULL);
}

void Character::move(float accx)
{
    this->acc.x = accx;
}

void Character::jump(float accy)
{
    this->speed.y = accy;
}

void Character::set_position()
{
    if (this->keystate[SDL_SCANCODE_LEFT]){
        this->move(-100);
    }
    else if (this->keystate[SDL_SCANCODE_RIGHT]){
        this->move(100);
    } else {
        this->move(0);
    }

    this->speed.x += (this->acc.x - this->speed.x*4)*delta_t;

    this->current_pos.x += this->speed.x*delta_t;

}

void Character::gravity(){
    this->speed.y += this->acc.y*delta_t;
    this->current_pos.y += this->speed.y*delta_t;

    if(this->current_pos.y < 5)
    {
        this->current_pos.y = 5;
        this->speed.y = 0;
    }
   
    if(this->speed.y > 0)
    { 
        if(this->speed.y <= 0.02*g)
        {
            this->speed.y = 0;
        }
        else
        {
            this->speed.y -= g*delta_t;
        }
    }  
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


void Character::manageEvents(SDL_Event e){
    if(e.type == SDL_KEYDOWN){
        // printf("touche pressee (code = %d)\n", e.key.keysym.sym);
        if (e.key.keysym.sym == SDLK_UP)
        {
            this->jump(70);
        }
    }
}

/*
bool verif_intersection(Character R1,Square R2){
    float x1min = R1.get_current_pos().x+0.5*R1.width; 
    float x1max = R1.current_pos.x-0.5*R1.width; 
    float y1min = R1.current_pos.x-0.5*R1.width; 
    float y1max = R1.current_pos.x+0.5*R1.width; 

    float x2min = R2.pos_square.x+0.5*R2.width; 
    float x2max = R2.pos_square.x-0.5*R2.width; 
    float y2min = R2.pos_square.x-0.5*R2.width; 
    float y2max = R2.pos_square.x+0.5*R2.width; 

    if y1max  < y2min : return false  // (1)
    if y1min > y2max  : return false  // (2)
    if x1min > x2max  : return false  // (3)
    if x1max  < x2min : return false  // (4)
    
    return true  // non empty intersection
}*/
