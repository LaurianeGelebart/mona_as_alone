#ifndef MENU_H
#define MENU_H 

#include <SDL2/SDL.h>
#include "Scene.h"
#include "Square.h"

class Menu : public Scene
{
    private:
       int selected_level;
       int nb_levels;
       Square arrow_left ; 
       Square arrow_right ;
       Square background ;  

    public:
        Menu();
        void draw();
        void manageEvents(SDL_Event);
        int get_selected_level();

}; 

#endif