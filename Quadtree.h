#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "Character.h"
#include "Platform.h"
#include "Scene.h"
#include "Camera2D.h"

struct SquareCorner {
    float x1;
    float x2;
    float y1;
    float y2;
};

struct Node{
    SquareCorner square;
    std::vector<Square> _objects;
    Node *topleft=nullptr;
    Node *botleft=nullptr;
    Node *topright=nullptr;
    Node *botright=nullptr;  
};

struct Leaf{
    std::vector<Square> _squares;
};

class Quadtree
{
    private:
    Node node;
    Character* chara;
    
    public:
    Node* quadtree(float width, float height);
    void addNode(Node* node, float x1, float x2, float y1, float y2);
    bool is_leaf();
    bool is_inside();
    void object_inside(int nb_square, Square* tab_square);
    bool test_corner(Position pos);
};

#endif