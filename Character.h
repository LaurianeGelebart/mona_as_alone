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
        Position old_pos; 
        Color color;
        const Uint8* keystate;
        bool has_win ; 
    
    public : 
        Character(int height, int width, Position pos, Position final_pos); 
        void move(float accx);
        void jump(float accy);
        void draw_character(int filled);
        void draw_end_pos();
        void gravity();
        void manageEvents(SDL_Event e);
        bool verif_intersection(Square R1,Square R2);  
        void set_speed_x(float speed);
        void set_speed_y(float speed);
        void set_position();
        void set_has_win(bool boolean);
        void set_old_position(Position old_pos);
        Position get_old_position();
        Position get_start_pos() ; 
        Position get_pos_end();
        float get_speed_x();
        float get_speed_y();
        bool get_has_win();
        Vect speed;
        Vect acc;
        
};


#endif