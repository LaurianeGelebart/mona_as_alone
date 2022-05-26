#include <vector>
#include "Character.h"
#include "Level.h"
#include "Quadtree.h"
#include "gameEnv.h"

//initialisation du Quadtree
Node* Quadtree::quadtree(float width, float height, l){
    Node* node = new Node();
    addNode(node, 0, width, 0, height);
    return node;
}

void Quadtree::addNode(Node* node, float x1, float x2, float y1, float y2)
{
    node->square = { x1, x2, y1, y2 };
    
    float x=(x1+x2)/2.0;
    float y=(y1+y2)/2.0;

    //si ce noeud n'est pas une feuille, on lui ajoute des enfants.
    if (!is_leaf(node->square))
    {
        node->topleft=new Node();
        node->topright=new Node();
        node->botleft=new Node();
        node->botright=new Node();

        addNode(node->topleft,x1,x,y,y2);
        addNode(node->topright,x,x2,y,y2);
        addNode(node->botleft,x1,x,y1,y);
        addNode(node->botright,x,x2,y1,y);
    }
}


//regarde si this->node est une feuille)
bool Quadtree::is_leaf(SquareCorner square){
    int nb_object = nb_object_inside(VECTEUR); //
    if (nb_object<4){
        return true;
    }
    return false;
}


bool Quadtree::test_corner(Position pos){

    if(pos.x > this->node.square.x1 && pos.x < this->node.square.x2){

        if(pos.y > this->node.square.y1 && pos.y < this->node.square.y2){
            return true;
        }
    }
    return false;
}

std::vector<Square> Quadtree::object_inside(Level* level)
{
    std::vector<Square> objects_inside;

    /*//Verification pour les character
    for(int i = 0; i < level->get_nb_character(); i++){

        //on veut recupere les quatres coins de chacun des character, on teste ces coins pour savoir si ils sont dans la subdivision

        if(level->tab_character[i]->get_current_pos().x < this->node.square.x2 && level->tab_character[i]->get_current_pos().x > this->node.square.x1){
            if(level->tab_character[i]->get_current_pos().y < this->node.square.y2 && level->tab_character[i]->get_current_pos().y > this->node.square.y1){
                objects_inside.push_back(level->tab_character[i]);
            }
        }
    }*/

    //Verification pour les character
    for(int i = 0; i < level->get_nb_square(); i++){

        if(level->tab_square[i]->get_current_pos().x < this->node.square.x2 && level->tab_character[i]->get_current_pos().x > this->node.square.x1){
            if(level->tab_character[i]->get_current_pos().y < this->node.square.y2 && level->tab_character[i]->get_current_pos().y > this->node.square.y1){
                objects_inside.push_back(level->tab_character[i]);
            }
        }
    }


    return objects_inside;
}


bool Quadtree::is_inside(){

    this->chara = Level::get_current_character();
    if (test_corner(chara->get_left_upper_corner)){
       return true;
    }
    else if (test_corner(chara->get_left_lower_corner)){
        return true;
    }
    else if (test_corner(chara->get_right_upper_corner)){
        return true;
    }
    else if (test_corner(chara->get_right_lower_corner)){
        return true;
    }
    return false;
}

//compte combien d'objet sont dans this->node //surement réajuster avec les coins ?
int Quadtree::object_inside(SquareCorner square){
    int nb_object = 0;
    //verif pour tab_character 
    for (int i=0; i<get_current_scene()->nb_character; i++){
        if (get_current_scene()->tab_character[i].get_current_pos().x < square.x2  && get_current_scene()->tab_character[i].get_current_pos().x > square.x1 ){
          if (get_current_scene()->tab_character[i].current_pos().y < square.y2  && get_current_scene()->tab_character[i].get_current_pos().y > square.y1 ){
          nb_object += 1;
          }
        }
    }
    //verif tab_square du bon niveau
     for (int i=0; i<get_current_scene()->nb_square; i++){
        if (get_current_scene()->tab_square[i].current_pos.x < square.x2  && get_current_scene()->tab_square[i].current_pos.x > square.x1 ){
          if (get_current_scene()->tab_square[i].current_pos.y < square.y2  && get_current_scene()->tab_square[i].current_pos.y > square.y1 ){
          nb_object += 1;
          }
        }
    }
    return nb_object;
}
