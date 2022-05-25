#include "Character.h"
#include "Level.h"
#include "Quadtree.h"
#include "gameEnv.h"

//initialisation du Quadtree
Node* quadtree(float width, float height){
    Node* node = new Node();
    addNode(node, 0, width, 0, height);
    return node;
}

void addNode(Node* node, float x1, float x2, float y1, float y2)
{
    node->square = { x1, x2, y1, y2 };
    
    float x=(x1+x2)/2.0;
    float y=(y1+y2)/2.0;

    //si ce noeud n'est pas une feuille et contient le current character lui ajouter des enfants.
    if (!is_leaf(node->square) && is_inside(node->square) ) //x2-x1 > get_current_character().width ? pareil pour height ?
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
    //noeud qui nous intéresse vérifie is_leaf() et is_inside();
}


//regarde si this->node est une feuille)
bool is_leaf(SquareCorner square){
    int nb_object =object_inside(square);
    if (nb_object<4){
        return true;
    }
    return false;
}

bool is_inside(SquareCorner square){
    if (get_current_character()->current_character->get_current_pos().x < square.x2 && get_current_character()->current_character->get_current_pos().x > square.x1 ){
        if (get_current_character()->current_character->get_current_pos().y < square.y2  && get_current_character()->current_character->get_current_pos().y > square.y1){
            return true;
        }
    }
    return false;
}

//compte combien d'objet sont dans this->node //surement réajuster avec les coins ?
int object_inside(SquareCorner square){
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

/*
void Quadtree::insert(Node *node)
{
    //
}

Cette méthode va parcourir chaque nœuds du quadTree et récursivement les 4 sous nœuds(quadrants) dans 
lesquels l'AABB passé en paramètre se trouve(test de collision aussi ici avec les AABB représentant les quadrants). 
Ce parcours récursif va permettre d'identifier toutes les feuilles (noeuds qui contienne des AABB(celles du décors probablement) 
contenant des éléments susceptible d'être en collision avec le personnage.

Node* Quadtree::search(Square chara)
{
   //
}

bool Quadtree::inBoundary(Square square)
{
    //
}*/