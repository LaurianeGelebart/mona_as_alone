#include <SDL2/SDL.h>

#include "Win.h"
#include "geometry.h"
#include "Square.h"
#include "gameEnv.h"

Win::Win(){

    this->background = Square(205, 105, {96, 50});
    this->background.set_textID(Game_Environment::gentexture("images/bravo.png"));
}

void Win::draw(){

  this->background.draw_square();

}
