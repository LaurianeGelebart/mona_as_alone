#include <SDL2/SDL.h>

#include "Menu.h"
#include "geometry.h"
#include "Square.h"
#include "Square.h"

Menu::Menu(){
    this->selected_level = 0 ; 
    this->nb_levels = 3 ;
    
    Square left = Square(4, 5, {105, 75});

    Square right = Square(4, 5, {155, 75});

    Square background  = Square(200, 200, {0, 0});
    
    this->arrow_left = left ; 
    this->arrow_right = right; 
    this->background = background; 

}


int Menu::get_selected_level(){
    return this->selected_level;
}

void Menu::draw(){

  //  drawSquare(fond); 

  this->arrow_left.drawSquare(); 
  this->arrow_right.drawSquare(); 

}

void Menu::manageEvents(SDL_Event e){
    if (e.type == SDL_KEYDOWN){

        if (e.key.keysym.sym == SDLK_UP)
        {
            this->selected_level -= 1;
            this->selected_level += this->nb_levels*(this->selected_level<0);
            this->arrow_left.set_pos_y(50-selected_level*10); 
            this->arrow_right.set_pos_y(50-selected_level*10);
           // printf("%d------------------\n", this->selected_level); //DEBUG
        }
        if (e.key.keysym.sym == SDLK_DOWN)
        {
            this->selected_level = (this->selected_level+1)%this->nb_levels;
            this->arrow_left.set_pos_y(50-selected_level*10); 
            this->arrow_right.set_pos_y(50-selected_level*10);
        }
        if (e.key.keysym.sym == SDLK_h)
        {
            this->selected_level = 0;
        }
	}
}