#ifndef GEOMETRY_H
#define GEOMETRY_H 

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

#endif