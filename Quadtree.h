#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "Character.h"
#include "Level.h"
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
    bool is_leaf(SquareCorner square);
    bool is_inside();
    int nb_object_inside(std::vector<Square> vector);
    std::vector<Square> object_inside(Level* level);
    bool test_corner(Position pos);
};

#endif