#include <vector>
#include "Character.h"
#include "Level.h"
#include "Quadtree.h"
#include "gameEnv.h"

//initialisation du Quadtree
Node* Quadtree::quadtree(float width, float height){
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
    if (!is_leaf())
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
bool Quadtree::is_leaf(){

    if ((this->node.square.x2 - this->node.square.x1) < 10.0){
        return true; 
    }
    return false;
}


bool Quadtree::test_corner(Position pos){

    if(pos.x >= this->node.square.x1 && pos.x <= this->node.square.x2){

        if(pos.y >= this->node.square.y1 && pos.y <= this->node.square.y2){
            return true;
        }
    }
    return false;
}

void Quadtree::object_inside(int nb_square, Square* tab_square)
{
    //Verification pour les squares
    for(int i = 0; i < nb_square; i++){
        if(test_corner(tab_square[i].get_left_lower_corner()) || test_corner(tab_square[i].get_left_upper_corner()) || test_corner(tab_square[i].get_right_lower_corner()) || test_corner(tab_square[i].get_right_upper_corner())){
             this->node._objects.push_back(tab_character[i]);
        }
    }
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

