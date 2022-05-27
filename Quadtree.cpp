#include <vector>
#include "Character.h"
#include "Level.h"
#include "Quadtree.h"
#include "gameEnv.h"

//initialisation du Quadtree
Node* Quadtree::init_quadtree(float width, float height, Square* tab_square, int nb_square){

    Node* node = new Node();
    for (int i = 0; i <nb_square; i++){
        node->_objects[i] = tab_square[i];
    }
    node->nb_object = nb_square;
    node->square = { 0, width, 0, height };
    return node;
}

void Quadtree::addNode(Node* quadtree)
{
    quadtree->botleft = new Node();
    quadtree->topleft = new Node();
    quadtree->topright = new Node();
    quadtree->botright = new Node();

    float x = (quadtree->square.x1 + quadtree->square.x2)/2.0;
    float y = (quadtree->square.y1 + quadtree->square.y2)/2.0;

    quadtree->botleft->square = { quadtree->square.x1, x, quadtree->square.y1, y };
    quadtree->topleft->square = { quadtree->square.x1, x, y, quadtree->square.y2 };
    quadtree->topright->square = { x, quadtree->square.x2, y, quadtree->square.y2 };
    quadtree->botright->square = { x, quadtree->square.x2, quadtree->square.y1, y };

    quadtree->botleft->nb_object = 0;
    quadtree->topleft->nb_object = 0;
    quadtree->topright->nb_object = 0;
    quadtree->botright->nb_object = 0;  
}

void Quadtree::object_inside(Node* child, Square object_parent[30], int nb_object_parent){

    for (int i = 0; i< nb_object_parent; i++){
        if(test_corner(object_parent[i].get_left_lower_corner(),child) || test_corner(object_parent[i].get_right_lower_corner(),child) || 
            test_corner(object_parent[i].get_left_upper_corner(),child) || test_corner(object_parent[i].get_right_upper_corner(),child)){

            child->_objects[child->nb_object]=object_parent[i];
            child->nb_object += 1;
        }
    }
}

//regarde si this->node est une feuille)
bool Quadtree::is_leaf(Node* node){

    if (node.botleft==nullptr && node.topleft==nullptr && node.botright==nullptr && node.topright==nullptr){
        return true; 
    }
    return false;
}


bool Quadtree::test_corner(Position pos, Node* child){

    if(pos.x >= child->square.x1 && pos.x <= child->square.x2){

        if(pos.y >= child->square.y1 && pos.y <= child->square.y2){
            return true;
        }
    }
    return false;
}



void Quadtree::make_quadtree(Node* quadtree){

    addNode(quadtree);
    
    object_inside(quadtree->botleft, quadtree->_objects, quadtree->nb_object);
    object_inside(quadtree->botright, quadtree->_objects, quadtree->nb_object);
    object_inside(quadtree->topright, quadtree->_objects, quadtree->nb_object);
    object_inside(quadtree->topleft, quadtree->_objects, quadtree->nb_object);

    if(quadtree->nb_object > 4){
        if(quadtree->botleft->nb_object > 4){
            make_quadtree(quadtree->botleft);
        }
        if(quadtree->botright->nb_object > 4){
            make_quadtree(quadtree->botright);
        }
        if(quadtree->topright->nb_object > 4){
            make_quadtree(quadtree->topright);
        }
        if(quadtree->topleft->nb_object > 4){
            make_quadtree(quadtree->topleft);
        }
    }
}

Node* Quadtree::test_corner_recursive(Position pos, Node* node){

    Node* nodebotleft = node->botleft;
    Node* nodebotright = node->botright;
    Node* nodetopright = node->topright;
    Node* nodetopleft = node->topleft;


    if(is_leaf(node)){
        return node;
    }
    
    if(pos.x >= nodebotleft->square.x1 && pos.x <= nodebotleft->square.x2){

        if(pos.y >= nodebotleft->square.y1 && pos.y <= nodebotleft->square.y2){
            return test_corner_recursive(pos.x, pos.y, nodebotleft);
        }
        return test_corner_recursive(pos.x, pos.y, nodetopleft);
    }
    else if (pos.y >= nodebotright->square.y1 && pos.y <= nodebotright->square.y2)
    {
        return test_corner_recursive(pos.x, pos.y, nodebotright);
    }
    return test_corner_recursive(pos.x, pos.y, nodetopright); 
}


/*bool Quadtree::compare_leaf(Node* first, Node* second){
    if(first->square.x1 == second->square.x1 && first->square.y1 == second->square.y1){
        return true;
    }
    return false;
}*/


/*void Quadtree::addNode(Node* node, float x1, float x2, float y1, float y2)
{
    node->square = { x1, x2, y1, y2 };
    
    float x=(x1+x2)/2.0;
    float y=(y1+y2)/2.0;
    //si ce noeud n'est pas une feuille, on lui ajoute des enfants.
    if (this->node.square.x2 - this->node.square.x1) > 10.0)
    {
        Node* node->topleft=new Node();
        node->topright=new Node();
        node->botleft=new Node();
        node->botright=new Node();

        

        addNode(node->topleft,x1,x,y,y2);
        addNode(node->topright,x,x2,y,y2);
        addNode(node->botleft,x1,x,y1,y);
        addNode(node->botright,x,x2,y1,y);
    }
}*/

/*bool Quadtree::is_inside(){

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
}*/