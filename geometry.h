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

Position operator + (Position a, Position b); 
Position operator - (Position a, Position b); 
float operator ^ (Position a, Position b); 

#endif