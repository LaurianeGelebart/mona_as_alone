#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
    private : 
        int width;
        int height;
        Position start_pos;
        Position end_pos;
        Position current_pos;
        Color color;
        int air;
    
    public : 
        void move(float accx);
        void jump(float accy);
        void draw_character(int filled);
        void init_Character(int height, int width, Position pos, Position final_pos); 
        void set_current_pos(Position current_pos);
        void set_position();
        Vect speed;
        Vect acc;
};


#endif