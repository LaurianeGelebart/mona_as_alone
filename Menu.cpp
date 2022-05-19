#include <SDL2/SDL.h>

#include "Menu.h"

Menu::Menu():selected_level(0), nb_levels(3){}


int Menu::get_selected_level(){
    return this->selected_level;
}

void Menu::draw(){
    printf("Menu\n"); //DEBUG

}

void Menu::manageEvents(SDL_Event e){
    if (e.type == SDL_KEYDOWN){
        printf("M\n");

        if (e.key.keysym.sym == SDLK_UP)
        {
            this->selected_level -= 1;
            this->selected_level += this->nb_levels*(this->selected_level<0);
        }
        if (e.key.keysym.sym == SDLK_UP)
        {
            this->selected_level = (this->selected_level+1)%this->nb_levels;
        }
        if (e.key.keysym.sym == SDLK_h)
        {
            this->selected_level = 0;
        }
	}
}