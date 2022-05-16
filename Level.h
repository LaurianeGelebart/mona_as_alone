#ifndef LEVEL_H
#define LEVEL_H

class Level 
{
    private: 
        int nb_character ; 
        int nb_character_end ; 
        int current_character ; 
        int nb_square;

    public:
        void init_level(Square* tab_square, Character* tab_character, int nb_character, int nb_square);
        void set_nb_character_end(int nb_character_end);
        void set_current_character(int new_current);
        void draw();
        int event();
        Character* tab_character ; 
        Square* tab_square ;
};

#endif
