#include "Scene_holder.h"

Scene_holder::Scene_holder(Scene** tab_level, Scene* menu){
    this->menu = menu ; 
    this->tab_level = tab_level ; 
    this->current_scene = this->menu ; 
}

Scene_holder::Scene_holder(){
}

void Scene_holder::change_to_menu(){
    this->current_scene = this->menu ; 
}

void Scene_holder::change_to_level(int level){
    this->current_scene = this->tab_level[level] ; 
}
Scene * Scene_holder::get_current_scene(){
    return this->current_scene ; 
} 



