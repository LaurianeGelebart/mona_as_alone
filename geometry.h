#ifndef GEOMETRY_H
#define GEOMETRY_H 

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Vect
{
    float x;
    float y;
};

typedef Vect Position;

struct Square
{
    int width; 
    int height; 
    Position pos_square; 
};


void drawSquare(int filled,float width, float height, float x, float y) ;

#endif