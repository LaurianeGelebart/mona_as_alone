/*****************************************************************************
Quadtree (à revoir --', ne pas mettre le cpp dans le makefile --') mais contient:
- initialisation d'une case à la taille du background
- fabrication du quadtree, jusqu'à obtenir des cases ne contenant que 4 blocs
- fonction qui récupère les 4 plus petites cases, contenant chacune un coin 
  du personnage et qui retourne la liste des blocs contenus dans ces cases. Si 
  deux coins sont dans la même case on récupère qu'une seule fois les blocs 
  contenus dans la case.
*******************************************************************************/
#include <list>
#include "Character.h"
#include "Level.h"
#include "Quadtree.h"
#include "gameEnv.h"

//initialisation du Quadtree
Node* init_quadtree(float width, float height, Platform* tab_square, int nb_square){
    
    Node* node = new Node();
    for (int i = 0; i <nb_square; i++){
        node->block_list.insert(i,tab_square[i]);
    }
    node->square = { 0, width, 0, height };
    return node;
}

void addNode(Node* quadtree)
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
}
    
std::list<Platform> blocks_inside(Node* child, std::list<Platform>& list){
    
    //clear the list before checking
    child->block_list.clear();

    for (std::list<Platform>::iterator it = list.begin(); it != list.end(); it++){
        if(test_corner(list[it].get_left_lower_corner(),child) || test_corner(list[it].get_right_lower_corner(),child) || 
            test_corner(list[it].get_left_upper_corner(),child) || test_corner(list[it].get_right_upper_corner(),child)){

            child->block_list.push_back(it);
        }
    }
    return child->block_list;
}

//regarde si on est une feuille
bool is_leaf(Node* node){

    if (node->botleft==nullptr && node->topleft==nullptr && node->botright==nullptr && node->topright==nullptr){
        return true; 
    }
    return false;
}


bool test_corner(Position pos, Node* child){

    if(pos.x >= child->square.x1 && pos.x <= child->square.x2){

        if(pos.y >= child->square.y1 && pos.y <= child->square.y2){
            return true;
        }
    }
    return false;
}

void make_quadtree(Node* quadtree){

    addNode(quadtree);
    
    quadtree->botleft->block_list = blocks_inside(quadtree->botleft, quadtree->block_list);
    quadtree->topleft->block_list = blocks_inside(quadtree->topleft, quadtree->block_list);
    quadtree->botright->block_list = blocks_inside(quadtree->botright, quadtree->block_list);
    quadtree->topright->block_list = blocks_inside(quadtree->topright, quadtree->block_list);

    if(quadtree->block_list.size() > 4){
        if(quadtree->botleft->block_list.size() > 4){
            make_quadtree(quadtree->botleft);
        }
        if(quadtree->botright->block_list.size() > 4){
            make_quadtree(quadtree->botright);
        }
        if(quadtree->topright->block_list.size() > 4){
            make_quadtree(quadtree->topright);
        }
        if(quadtree->topleft->block_list.size() > 4){
            make_quadtree(quadtree->topleft);
        }
    }
}

Node* test_corner_recursive(Position pos, Node* node){

    if(is_leaf(node)){
        return node;
    }
    
    if(pos.x >= node->botleft->square.x1 && pos.x <= node->botleft->square.x2){

        if(pos.y >= node->botleft->square.y1 && pos.y <= node->botleft->square.y2){
            return test_corner_recursive(pos.x, pos.y, node->botleft);
        }
        return test_corner_recursive(pos, node->topleft);
    }
    else if (pos.y >= node->botright->square.y1 && pos.y <= node->botright->square.y2)
    {
        return test_corner_recursive(pos, node->botright);
    }
    return test_corner_recursive(pos, node->topright); 
}

 std::list<Platform> get_blocks_in_zone(Character* chara, Node* node){

    Node* zone;
    zone->botleft = test_corner_recursive(chara->get_left_lower_corner(),node);
    zone->botright = test_corner_recursive(chara->get_right_lower_corner(),node);
    zone->topleft = test_corner_recursive(chara->get_left_upper_corner(),node);
    zone->topright = test_corner_recursive(chara->get_right_upper_corner(),node);

    int nb_object = zone->botleft->block_list.size()+zone->topright->block_list.size()+zone->botright->block_list.size()+zone->topleft->block_list.size();
    
    for (int i=0; i<nb_object;i++){
        zone->block_list.push_back(zone->botleft->block_list(i));
        if (zone->topleft->block_list(i)!=zone->botleft->block_list(i))
        {
            zone->block_list.push_back(zone->topleft->block_list(i));
        } 
        if (zone->topright->block_list(i)!=zone->topleft->block_list(i) && zone->topright->block_list(i)!=zone->botleft->block_list(i))
        {
            zone->block_list.push_back(zone->topright->block_list(i));
        }
        if (zone->botright->block_list(i)!=zone->topright->block_list(i)&& zone->botright->block_list(i)!=zone->topleft->block_list(i) && zone->botright->block_list(i)!=zone->botleft->block_list(i))
        {
            zone->block_list.push_back(zone->botright->block_list(i));
        } 
    }  
    return zone->block_list;
 }