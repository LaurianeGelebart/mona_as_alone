#ifndef LEVEL_H
#define LEVEL_H

#include "Character.h"
#include "Scene.h"
#include "Camera2D.h"

class Level : public Scene 
{
    private: 
        int nb_character ; 
        int nb_square ; 
        int selected_character ;
        int nb_character_end ;
        Character *current_character ; 
        Camera2D level_cam;  
        float alpha ; 
        

    public:
        Level(Square* tab_square, Character* tab_character[], int nb_square, int nb_character);
        void set_nb_character_end(int nb_character_end);
        void set_current_character(int new_current);
        void set_alpha(float alpha);
        void manageEvents(SDL_Event);
        int get_nb_character();
        int get_nb_character_end();
        Character* get_current_character();
        void draw();
        Character** tab_character ; 
        Square* tab_square ;
        
};

#endif
