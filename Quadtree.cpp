#include "Character.h"
#include "Level.h"
#include "Quadtree.h"
#include "Square.h"

void Quadtree::insert(Node *node)
{
    //
}

/*Cette méthode va parcourir chaque nœuds du quadTree et récursivement les 4 sous nœuds(quadrants) dans 
lesquels l'AABB passé en paramètre se trouve(test de collision aussi ici avec les AABB représentant les quadrants). 
Ce parcours récursif va permettre d'identifier toutes les feuilles (noeuds qui contienne des AABB(celles du décors probablement) 
contenant des éléments susceptible d'être en collision avec le personnage.*/

Node* Quadtree::search(Square chara)
{
   //
}

bool Quadtree::inBoundary(Square square)
{
    //
}