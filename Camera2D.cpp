
#include "Camera2D.h" 

 void Camera2D::set_position(Position pos){
     if (pos.x <0 ) { pos.x= 0 ; } 
     if (pos.x > 100 ) { pos.x = 100 ; } 
     this->pos= pos;
 }