#include <SDL2/SDL.h>

#include "Controls.h"
#include "geometry.h"
#include "Square.h"
#include "gameEnv.h"

Controls::Controls(){

    this->background = Square(205, 105, {100, 50});
    this->background.set_textID(Game_Environment::gentexture("images/commandes.png"));
}

void Controls::draw(){
  this->background.draw_square();

}