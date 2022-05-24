#pragma once

#include <string>
#include "Level.h"
#include "Scene.h"
#include "Menu.h"

class Game_Environment
{
    private: 
        Menu* menu ; 
        Level** tab_level ; 
        Scene* current_scene ; 
        int game_loop;

    public:
        Game_Environment(Level** tab_level, Menu* menu);
        Game_Environment();
        Scene * get_current_scene();
        void change_to_menu();
        void change_to_level(int level);
        static GLuint gentexture(std::string path);
        void manageEvents();
        void draw();
        int is_playing();
        void is_win() ; 
        void onWindowResized(unsigned int width, unsigned int height);
        int is_in_menu();
};


