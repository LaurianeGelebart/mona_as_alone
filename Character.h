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
        Square end_zone ; 
    
    public : 
        Character(int height, int width, float jumpforce, Position pos, Position final_pos); 
        void move(float accx);
        void jump(float accy);
        void draw_character();
        void draw_indice(float alpha);
        void gravity();
        void manageEvents(SDL_Event e);
        bool verif_intersection(Square R1,Square R2);  
        void set_speed_x(float speed);
        void set_speed_y(float speed);
        void set_position();
        void set_jump(bool jump);
        void set_has_win(bool boolean);
        Position get_start_pos() ; 
        Position get_pos_end();
        float get_speed_x();
        float get_speed_y();
        bool get_has_win();
        bool get_isjumping();
        void switch_gravity();
        bool is_switch_gravity();
        Square get_end_zone();
        void set_end_zone(Position pos);
        bool in_jump;
        Vect speed;
        Vect acc;
        float jumpforce;
        
};


#endif