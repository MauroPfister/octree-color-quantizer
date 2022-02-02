#pragma once

#include <vector>
#include <array>
#include "Node.h"
#include "Color.h"

class ColorOctree {
    static const int MAX_LEVEL = 8;  // Max depth of octree (8 for 8 bit image)
    Node *root;
    int n_nodes;
    int n_leaves;
    std::array<std::vector<Node *>, MAX_LEVEL> levels;
    int index_at_level(Color col, int level);

    public:
        ColorOctree();
        void add_color(Color col);
        void reduce_tree(int k);
        Color get_palette_color(Color col);
};