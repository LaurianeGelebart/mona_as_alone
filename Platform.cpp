#include "Square.h"
#include "Platform.h"

Platform::Platform(int width, int height, Position current_pos){
    this->width = width ; 
    this->height = height ; 
    this->current_pos = current_pos ; 
}

Platform::Platform(){ 
}

/*
void Platform::set_pos_x(float x){
    this->current_pos.x = x;
}

void Platform::set_pos_y(float y){
    this->current_pos.y = y;
}

void Platform::move_y(float y){
    this->current_pos.y+=y;
}

void Platform::move_x(float x){
    this->current_pos.x+=x;
}
*/