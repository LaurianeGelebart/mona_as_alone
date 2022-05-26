#ifndef CONTROLS_H 
#define CONTROLS_H 

#include <SDL2/SDL.h>
#include "Scene.h"
#include "Square.h"

class Controls : public Scene
{
    private:
       Square arrow_right ;
       Square background ;  

    public:
        Controls();
        void draw();

}; 

#endif