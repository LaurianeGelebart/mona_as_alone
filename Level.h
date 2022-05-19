#ifndef LEVEL_H
#define LEVEL_H

#include "Character.h"
#include "Scene.h"

class Level : public Scene 
{
    private: 
        int nb_character ; 
        int nb_character_end ; 
        Character *current_character ; 

    public:
        Level(Square* tab_square, Character* tab_character[], int nb_character);
        void set_nb_character_end(int nb_character_end);
        void set_current_character(int new_current);
        Character* get_current_character();
        void draw();
        void manageEvents(SDL_Event);
        Character** tab_character ; 
        Square* tab_square ;
};

#endif
