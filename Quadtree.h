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
    Square _objects[30];
    Node *topleft=nullptr;
    Node *botleft=nullptr;
    Node *topright=nullptr;
    Node *botright=nullptr;
    int nb_object; 
};

class Quadtree
{    
    public:
    Node* init_quadtree(float width, float height, Square* tab_square, int nb_square);
    void addNode(Node* quadtree);
    bool is_leaf(Node* node);
    Node* is_inside();
    void object_inside(Node* child, Square object_parent[30], int nb_object_parent);
    bool test_corner(Position pos, Node* child);
    Node* test_corner_recursive(Position pos, Node* node);
    void make_quadtree(Node* quadtree);
    //bool compare_leaf(Node* first, Node* second);
    //void get_four_leaves(Position pos, Node* node);
};

#endif