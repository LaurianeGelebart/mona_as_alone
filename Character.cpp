#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "constants.h"
#include "geometry.h"
#include "color.h"
#include "Character.h"
#include "Square.h"
    

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

    float tab_pos[4]; 
    this->get_positions(tab_pos) ; 

    glColor3f(this->color.r, this->color.g, this->color.b);

    glVertex2f( tab_pos[0], tab_pos[3]);
    glVertex2f( tab_pos[1], tab_pos[3]);
    glVertex2f( tab_pos[1], tab_pos[2]);
    glVertex2f( tab_pos[0], tab_pos[2]);

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


bool Character::verif_intersection(Square square){
    float tab_pos_character[4]; 
    this->get_positions(tab_pos_character) ; 
    float tab_pos_square[4]; 
    square.get_positions(tab_pos_square) ; 

    if (tab_pos_character[3]  < tab_pos_square[3]) { return false; }  // (1)
    if (tab_pos_character[2]  > tab_pos_square[2]) { return false; } // (2)
    if (tab_pos_character[0]  > tab_pos_square[1]) { return false; } // (3)
    if (tab_pos_character[1]  < tab_pos_square[0]) { return false; } // (4)
    
    else {return true ; } // non empty intersection
}
