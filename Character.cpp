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

Position Character::get_pos_end(){
    return this->end_pos ; 
}

void Character::set_speed_x(float speed){
    
    this->speed.x=speed;
}

void Character::set_speed_y(float speed){
    this->speed.y=speed;
}

float Character::get_speed_x(){
    return this->speed.x;
}

float Character::get_speed_y(){
    return this->speed.y;
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


void Character::set_old_position(Position old_pos){
    this->old_pos = old_pos ; 
}
Position Character::get_old_position(){
    return this->old_pos ; 
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

   // printf("\n\n %f \n\n", this->speed.y);
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

void Character::draw_end(){


    glColor3f(0.40, 0.40, 0.40);

    glBegin(GL_QUADS);
     //glTexCoord2f(0.,0.);
    glVertex2f( this->end_pos.x-0.5*this->width, this->end_pos.y+0.5*this->height);
    //glTexCoord2f(1.,0.);
    glVertex2f( this->end_pos.x+0.5*this->width, this->end_pos.y+0.5*this->height);
    //glTexCoord2f(1.,1.);
    glVertex2f( this->end_pos.x+0.5*this->width, this->end_pos.y-0.5*this->height);
    //glTexCoord2f(0.,1.);
    glVertex2f( this->end_pos.x-0.5*this->width, this->end_pos.y-0.5*this->height);


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

