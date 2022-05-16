#pragma once

//#include "Level.h"
#include "Scene.h"

class Scene_holder 
{
    private: 
         Scene* menu ; 
         Scene** tab_level ; 
         Scene* current_scene ; 

    public:
        Scene_holder(Scene** tab_level, Scene* menu);
        Scene_holder();
         void change_to_menu();
         void change_to_level(int level);
         Scene * get_current_scene();
};


