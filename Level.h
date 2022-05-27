#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Character.h"
#include "Platform.h"
#include "Scene.h"
#include "Camera2D.h"
#include "Quadtree.h"

class Level : public Scene 
{
    private: 
        int nb_character ; 
        int nb_square ; 
        int selected_character ;
        int nb_character_end ;
        Character *current_character ; 
        Camera2D level_cam;  
        float alpha ; 
        Square background ; 
        

    public:
        Level(Square* tab_square, Character* tab_character[], int nb_square, int nb_character, Square background);
        void set_nb_character_end(int nb_character_end);
        void set_current_character(int new_current);
        void set_alpha(float alpha);
        void manageEvents(SDL_Event);
        int get_nb_character();
        int get_nb_square();
        int get_nb_character_end();
        void reset_level() ; 
        int verif_intersection(Character* R1,Square R2);
        void verif_end_pos();
        Character* get_current_character();
        void draw();
        Character** tab_character ; 
        Square* tab_square ;
        Node* quadtree;

        /*void check_inside_zone(int nb_square, Square* tab_square, Node* quadtree);*/
        void collisions(Character* chara); 
        bool opposite_side(Position A,Position B,Position M,Position P);
        
};

#endif
