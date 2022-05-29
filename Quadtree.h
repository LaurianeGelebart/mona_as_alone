#ifndef QUADTREE_H
#define QUADTREE_H

#include <list>
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
    std::list<Platform> block_list;
    Node *topleft=nullptr;
    Node *botleft=nullptr;
    Node *topright=nullptr;
    Node *botright=nullptr;
};

void addNode(Node* quadtree);
void make_quadtree(Node* quadtree);
bool is_leaf(Node* node);
bool test_corner(Position pos, Node* child);
Node* is_inside();
Node* test_corner_recursive(Position pos, Node* node);
Node* init_quadtree(float width, float height, Platform* tab_square, int nb_square);
std::list<Platform> blocks_inside(Node* child, std::list<Platform> list);
std::list<Platform> get_blocks_in_zone(Character* chara, Node* node);

#endif