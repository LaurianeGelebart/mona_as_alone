#ifndef CHARACTER_H
#define CHARACTER_H

#include "geometry.h"
#include "color.h"

class Character
{
    private : 
        int width;
        int height;
        Position start_pos;
        Position end_pos;
        Position current_pos;
        Color color;
        const Uint8* keystate;
    
    public : 
        Character(int height, int width, Position pos, Position final_pos); 
        void move(float accx);
        void jump(float accy);
        void draw_character(int filled);
        void set_current_pos(Position current_pos);
        void set_position();
        void manageEvents(SDL_Event e);
        Vect speed;
        Vect acc;
};


#endif