#include <SDL2/SDL.h>

#include "Menu.h"
#include "geometry.h"
#include "Square.h"
#include "gameEnv.h"

Menu::Menu(){
    this->selected_level = 0 ; 
    this->nb_levels = 3 ;
    
    Square left = Square(4, 5, {108, 52.5});

    Square right = Square(4, 5, {155, 52.5});

    Square background  = Square(205, 105, {100, 50});
    
    this->arrow_left = left ;
    this->arrow_left.set_textID(Game_Environment::gentexture("images/arrow_left.png"));
    this->arrow_right = right;
    this->arrow_right.set_textID(Game_Environment::gentexture("images/arrow_right.png"));
    this->background = background;
    this->background.set_textID(Game_Environment::gentexture("images/background_menu.png"));
}


int Menu::get_selected_level(){
    return this->selected_level;
}

void Menu::draw(){

  this->background.draw_square();
  this->arrow_left.draw_square(); 
  this->arrow_right.draw_square(); 

}

void Menu::manageEvents(SDL_Event e){
    if (e.type == SDL_KEYDOWN){

        if (e.key.keysym.sym == SDLK_UP)
        {
            this->selected_level -= 1;
            this->selected_level += this->nb_levels*(this->selected_level<0);
            this->arrow_left.set_pos_y(52.5-selected_level*10.5); 
            this->arrow_right.set_pos_y(52.5-selected_level*10.5);
           // printf("%d------------------\n", this->selected_level); //DEBUG
        }
        if (e.key.keysym.sym == SDLK_DOWN)
        {
            this->selected_level = (this->selected_level+1)%this->nb_levels;
            this->arrow_left.set_pos_y(52.5-selected_level*10.5); 
            this->arrow_right.set_pos_y(52.5-selected_level*10.5);
        }
        if (e.key.keysym.sym == SDLK_h)
        {
            this->selected_level = 0;
        }
	}
}