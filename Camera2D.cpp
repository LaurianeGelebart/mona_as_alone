
#include "Camera2D.h" 

 void Camera2D::set_position(Position pos){
     if (pos.x < 0 ) { pos.x= 0 ; } 
     if (pos.x > 50 ) { pos.x = 50 ; }
     if (pos.y > 49 ) { pos.y = 49 ; }  
     this->pos= pos;
 }