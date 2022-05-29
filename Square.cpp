#include <SDL2/SDL.h>

#include "Square.h"
#include "geometry.h"


void Square::draw_square() 
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,this->_textID);

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
        
        //glColor3f(0.1, 0.2, 0.5);

        glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);    
    
}

void Square::draw_endzone(int filled) 
{  
     glLineWidth(3);

    if(filled)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }

        float tab_pos[4]; 

        glPushMatrix();
            glColor3f(0.8, 0, 0.5);
        glPopMatrix();

        tab_pos[0] = this->current_pos.x-0.5*this->width ; 
        tab_pos[1] = this->current_pos.x+0.5*this->width ; 

        tab_pos[2] = this->current_pos.y-0.5*this->height ; 
        tab_pos[3] = this->current_pos.y+0.5*this->height ; 
        glVertex2f(tab_pos[0],tab_pos[3]);
        glVertex2f(tab_pos[1],tab_pos[3]);
        glVertex2f(tab_pos[1],tab_pos[2]);
        glVertex2f(tab_pos[0],tab_pos[2]);
        
        glPushMatrix();
            glColor3f(1, 1, 1);
        glPopMatrix(); 
    glEnd();
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

GLuint Square::get_textID(){
    return _textID;
}
void Square::set_textID(GLuint textID){
    _textID = textID;
}
