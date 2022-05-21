#ifndef CHARACTER_H
#define CHARACTER_H

#include "Square.h"
#include "geometry.h"
#include "color.h"

class Character : public Square 
{
    private : 
        Position start_pos;
        Position end_pos;
        Color color;
        const Uint8* keystate;
    
    public : 
        Character(int height, int width, Position pos, Position final_pos); 
        void move(float accx);
        void jump(float accy);
        void draw_character(int filled);
        void set_position();
        void gravity();
        void manageEvents(SDL_Event e);
        bool verif_intersection(Square square); 
        Vect speed;
        Vect acc;
        Position current_pos;
        
};


#endif