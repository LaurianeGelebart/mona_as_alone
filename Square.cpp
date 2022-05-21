#include <SDL2/SDL.h>

#include "Square.h"


void Square::drawSquare() 
{
    float tab_pos[4]; 
    get_positions(tab_pos);

    glBegin(GL_QUADS);

    glVertex2f(tab_pos[0],tab_pos[3]);
    glVertex2f(tab_pos[1],tab_pos[3]);
    glVertex2f(tab_pos[1],tab_pos[2]);
    glVertex2f(tab_pos[0],tab_pos[2]);
    
    glColor3f(0.1, 0.2, 0.5);

    glEnd();
    
}

Square::Square(){}

Square::Square(int width, int height, Position current_pos){
    this->width = width ; 
    this->height = height ; 
    this->current_pos = current_pos ; 
}

void Square::get_positions(float* tab_pos){

    tab_pos[0] = this->current_pos.x-0.5*this->width ; 
    tab_pos[1] = this->current_pos.x+0.5*this->width ; 

    tab_pos[2] = this->current_pos.y-0.5*this->height ; 
    tab_pos[3] = this->current_pos.y+0.5*this->height ; 

}

Position Square::get_current_pos() {
    return this->current_pos  ; 
}

// void Square::set_pos_x(float x){
//     this->current_pos.x = x;
// }

void Square::set_pos_y(float y){
    this->current_pos.y = y;
}

void Square::move_y(float y){
    this->current_pos.y+=y;
}

