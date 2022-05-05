#ifndef QUADTREE_H
#define QUADTREE_H

// ce que l'on veut stocker dans le quadtree (les AABB des blocs susceptibles d'entrer en collisions)
struct Node
{
    Square square;
    int data;
    Node(Square _square, int _data)
    {
        square = _square;
        data = _data;
    }
    Node()
    {
        data = 0; //initialisation
    }
};

class Quadtree
{

    //Limites du noeud
        Position topLeft; //un point en haut à gauche
        Position botRight; //un point en bas à droite
    
        // Détails du noeud
        Node *n;
    
        //les 4 enfants
        Quadtree *topLeftTree;
        Quadtree *topRightTree;
        Quadtree *botLeftTree;
        Quadtree *botRightTree;
    
    public:
        Quadtree() //initialisation quadtree
        {
            topLeft.x = 0;
            topLeft.y = 0;
            botRight.x = 0;
            botRight.y = 0;

            n = NULL;
            topLeftTree  = NULL;
            topRightTree = NULL;
            botLeftTree  = NULL;
            botRightTree = NULL;
        }
        //creation quadtree definie par coin superieur gauche et coin inferieur droit, a adapter eventuellement
        Quadtree(Position topL, Position botR) //centre du quadtree, idealement : caracteristiques de notre personnage en parametres
        {
            n = NULL;
            topLeftTree  = NULL;
            topRightTree = NULL;
            botLeftTree  = NULL;
            botRightTree = NULL;
            topLeft = topL;
            botRight = botR;
        }
        void insert(Node*); //inserer un noeud dans un quadtree existant
        Node* search(Square); //cherche si un noeud se trouve dans un des quad existants
        bool inBoundary(Square); //verifie si le quadtree contient le rectangle/carree
};

#endif