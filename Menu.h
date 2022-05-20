#ifndef MENU_H
#define MENU_H 

#include <SDL2/SDL.h>
#include "Scene.h"

class Menu : public Scene
{
    private:
       int selected_level;
       int nb_levels;

    public:
        Menu();
        void draw();
        void manageEvents(SDL_Event);

        int get_selected_level();

        
}; 

#endif