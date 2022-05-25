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
        bool has_win ; 
    
    public : 
        Character(int height, int width, Position pos, Position final_pos); 
        void move(float accx);
        void jump(float accy);
        void draw_character();
        void draw_indice();
        void draw_end_pos();
        void gravity();
        void manageEvents(SDL_Event e);
        bool verif_intersection(Square R1,Square R2);  
        void set_speed_x(float speed);
        void set_speed_y(float speed);
        void set_position();
        void set_has_win(bool boolean);
        Position get_start_pos() ; 
        Position get_pos_end();
        float get_speed_x();
        float get_speed_y();
        bool get_has_win();
        bool get_isjumping();
        void set_jump(bool jump);
        bool in_jump ;
        Vect speed;
        Vect acc;
        
};


#endif