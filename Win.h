#ifndef WIN_H
#define WIN_H 

#include <SDL2/SDL.h>
#include "Scene.h"
#include "Square.h"

class Win : public Scene
{
    private:
       Square background ;  

    public:
        Win();
        void draw();

}; 

#endif