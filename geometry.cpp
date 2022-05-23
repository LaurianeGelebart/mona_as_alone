#include "geometry.h"

Position operator + (Position a, Position b)
{
        Position temp = Position{a.x + b.x ,  a.y + b.y} ; 
        return temp;
}

Position operator - (Position a, Position b)
{
        Position temp = Position{a.x - b.x ,  a.y - b.y} ; 
        return temp;
}

float operator ^ (Position a, Position b)
{
        float temp = a.x * b.y - a.y * b.x ; 
        return temp;
}
