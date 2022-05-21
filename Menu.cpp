#include <SDL2/SDL.h>

#include "Menu.h"
#include "gameEnv.h"
#include "geometry.h"
#include "constants.h"

Menu::Menu(){
    this->selected_level = 0 ; 
    this->nb_levels = 3 ;
    
    Square left;
    left.width = 4;
    left.height = 4;
    left.pos_square= {45, 35};

    Square right;
    right.width = 4;
    right.height = 4;
    right.pos_square = {75,35};

    Square background;
    background.width =200;
    background.height=100;
    background.pos_square= {0, 0};
    
    
    this->arrow_left = left ; 
    this->arrow_right = right; 
    this->background = background;

}

int Menu::get_selected_level(){
    return this->selected_level;
}

void Menu::draw(){

//drawSquare(background);   
drawSquare(this->arrow_left); 
drawSquare(this->arrow_right); 

}

void Menu::manageEvents(SDL_Event e){
    if (e.type == SDL_KEYDOWN){

        if (e.key.keysym.sym == SDLK_UP)
        {
            this->selected_level -= 1;
            this->selected_level += this->nb_levels*(this->selected_level<0);
            this->arrow_left.pos_square.y += 10 ; 
            this->arrow_right.pos_square.y += 10 ;
        }
        if (e.key.keysym.sym == SDLK_DOWN)
        {
            this->selected_level = (this->selected_level+1)%this->nb_levels;
            this->arrow_left.pos_square.y -= 10 ; 
            this->arrow_right.pos_square.y -= 10 ;
        }
        if (e.key.keysym.sym == SDLK_h)
        {
            this->selected_level = 0;
        }
	}
}