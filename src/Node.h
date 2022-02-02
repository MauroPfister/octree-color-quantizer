#pragma once
#include "Color.h"

struct Node {
    Color color;
    int id;
    int pixel_count;
    Node *children[8];

    Node(int id);
    bool is_leaf();
    Color avg_color();
    int remove_children();
};