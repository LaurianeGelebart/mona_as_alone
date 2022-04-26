#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
    private : 
        int width;
        int height;
        Position start_pos;
        Position end_pos;
        float jump_power;
        Color color;
    
    public : 
        void move(int dx, int dy);
        void draw_character(int filled);
        void init_Character(int height, int width, Position pos, Position final_pos); 
        void set_current_pos(Position current_pos);
        Position current_pos;
};


#endif