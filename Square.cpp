#include <SDL2/SDL.h>

#include "Square.h"
#include "geometry.h"


void Square::draw_square() 
{

    /*glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,this->textID);*/

    float tab_pos[4]; 

    tab_pos[0] = this->current_pos.x-0.5*this->width ; 
    tab_pos[1] = this->current_pos.x+0.5*this->width ; 

    tab_pos[2] = this->current_pos.y-0.5*this->height ; 
    tab_pos[3] = this->current_pos.y+0.5*this->height ; 

    glBegin(GL_QUADS);
    glTexCoord2f(0.,0.);
    glVertex2f(tab_pos[0],tab_pos[3]);
    glTexCoord2f(1.,0.);
    glVertex2f(tab_pos[1],tab_pos[3]);
    glTexCoord2f(1.,1.);
    glVertex2f(tab_pos[1],tab_pos[2]);
    glTexCoord2f(0.,1.);
    glVertex2f(tab_pos[0],tab_pos[2]);
    
    glColor3f(0.1, 0.2, 0.5);

    glEnd();

    /*glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);*/    
    
}

Square::Square(){}

Square::Square(int width, int height, Position current_pos){
    this->width = width ; 
    this->height = height ; 
    this->current_pos = current_pos ; 
}

int Square::get_width(){
    return this->width;
}

int Square::get_height(){
    return this->height;
}

Position Square::get_left_upper_corner(){
    Position pos ; 

    pos.x = this->current_pos.x-0.5*this->width ; 
    pos.y = this->current_pos.y+0.5*this->height ; 

   return pos ; 
}

Position Square::get_right_upper_corner(){
    Position pos ; 

    pos.x = this->current_pos.x+0.5*this->width ; 
    pos.y = this->current_pos.y+0.5*this->height ; 

   return pos ; 
}

Position Square::get_left_lower_corner(){
    Position pos ; 

    pos.x = this->current_pos.x-0.5*this->width ; 
    pos.y = this->current_pos.y-0.5*this->height ; 

   return pos ; 
}

Position Square::get_right_lower_corner(){
    Position pos ; 

    pos.x = this->current_pos.x+0.5*this->width ; 
    pos.y = this->current_pos.y-0.5*this->height ; 

   return pos ; 
}

Position Square::get_current_pos() {
    return this->current_pos  ; 
}

void Square::set_pos_x(float x){
    this->current_pos.x = x;
}

void Square::set_pos_y(float y){
    this->current_pos.y = y;
}

void Square::move_y(float y){
    this->current_pos.y+=y;
}

void Square::move_x(float x){
    this->current_pos.x+=x;
}
