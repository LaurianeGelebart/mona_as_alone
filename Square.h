#ifndef SQUARE_H
#define SQUARE_H 

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "geometry.h"

class Square
{
    protected:
        int width; 
        int height; 
        Position current_pos;
        GLuint _textID;

    public:
        void draw_square();
        Position get_current_pos(); 
        void get_positions(float* tab_pos); 
        Square(int height, int width, Position pos);    
        Square();
        GLuint get_textID();
        void set_textID(GLuint textID);
        void set_pos_x(float x);
        void set_pos_y(float y);
        void move_y(float y);
        void move_x(float x);

}; 

#endif