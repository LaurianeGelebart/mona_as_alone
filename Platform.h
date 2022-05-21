#ifndef PLATFORM_H
#define PLATFORM_H

class Platform
{
    private : 
        int width;
        int height;
        Position pos;
    
    public : 
        void move(float accx);
        void draw_platform(int filled);
        void init_platform(int height, int width, Position pos, Position final_pos); 
        void set_current_pos(Position current_pos);
        void set_position();
};


#endif