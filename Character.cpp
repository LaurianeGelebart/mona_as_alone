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
    this->has_win = 0 ; 
    this->in_jump = 0 ; 
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

bool Character::get_has_win(){
    return this->has_win;
}

void Character::set_has_win(bool boolean){
    this->has_win = boolean ; 
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

Position Character::get_start_pos(){
    return this->start_pos;
}

void Character::gravity(){
    this->speed.y += this->acc.y*delta_t;
    this->current_pos.y += this->speed.y*delta_t;
   
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

     if(this->current_pos.y < 0 -0.5*this->width)
    {
        this->current_pos = {5, 30}; 
    }

   // printf("\n\n %f \n\n", this->speed.y);
}


void Character::draw_character()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,this->_textID);

        glBegin(GL_QUADS);
        glTexCoord2f(0.,0.);
        glVertex2f( this->current_pos.x-0.5*this->width, this->current_pos.y+0.5*this->height);
        glTexCoord2f(1.,0.);
        glVertex2f( this->current_pos.x+0.5*this->width, this->current_pos.y+0.5*this->height);
        glTexCoord2f(1.,1.);
        glVertex2f( this->current_pos.x+0.5*this->width, this->current_pos.y-0.5*this->height);
        glTexCoord2f(0.,1.);
        glVertex2f( this->current_pos.x-0.5*this->width, this->current_pos.y-0.5*this->height);
    
    
    //glColor3f(this->color.r, this->color.g, this->color.b);
        
        glEnd(); 
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D); 
}

void Character::draw_indice()
{
    glPushMatrix();
        glColor3f(1, 1, 1);
    glPopMatrix(); 

    glBegin(GL_TRIANGLES);
    glVertex2f( this->current_pos.x, this->current_pos.y+2+0.5*this->height);
    glVertex2f( this->current_pos.x+0.25*5, this->current_pos.y+4+0.5*this->height);
    glVertex2f( this->current_pos.x-0.25*5, this->current_pos.y+4+0.5*this->height);
    

    glEnd(); 
}

void Character::draw_end_pos(){


   // glColor3f(0.40, 0.40, 0.40);

    glBegin(GL_QUADS);
     //glTexCoord2f(0.,0.);
    glVertex2f( this->end_pos.x-0.5*this->width, this->end_pos.y+0.5*this->height);
    //glTexCoord2f(1.,0.);
    glVertex2f( this->end_pos.x+0.5*this->width, this->end_pos.y+0.5*this->height);
    //glTexCoord2f(1.,1.);
    glVertex2f( this->end_pos.x+0.5*this->width, this->end_pos.y-0.5*this->height);
    //glTexCoord2f(0.,1.);
    glVertex2f( this->end_pos.x-0.5*this->width, this->end_pos.y-0.5*this->height);


   // glColor3f(this->color.r, this->color.g, this->color.b);

    glEnd(); 
}


void Character::manageEvents(SDL_Event e){
    if(e.type == SDL_KEYDOWN){
        // printf("touche pressee (code = %d)\n", e.key.keysym.sym);
        if (e.key.keysym.sym == SDLK_UP && !this->in_jump)
        {
            this->jump(70);
            this->in_jump = true;
        }
    }
}

bool Character::get_isjumping(){
    return this->in_jump;
}
void Character::set_jump(bool jump){
    this->in_jump = jump;
}
