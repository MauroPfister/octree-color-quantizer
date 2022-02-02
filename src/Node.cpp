#include <iostream>
#include "Node.h"
#include "Color.h"

Node::Node(int id)
    : color(0, 0, 0)
    , id(id)
    , pixel_count(0) 
    {
    // Initialize children with null pointer
    for (int i = 0; i <= 8; i++) {
        children[i] = nullptr;
    }
}

bool Node::is_leaf() {
    return pixel_count > 0;
}

Color Node::avg_color() {
    // Return color of node if pixel count is 0
    Color avg_col = pixel_count > 0 ? color.div(pixel_count) : color;
    return avg_col;
}

int Node::remove_children() {
    // No change in number of leaf nodes if node itself is a leaf.
    if (is_leaf()) {
        return 0;
    }
    // If no children are removed but the node becomes a leaf node 
    // the net subtraction of leaf nodes is -1.
    int removed = -1;

    for (Node *child : children) {
        if (child == nullptr) {
            continue;
        }
        color.add(child->color);
        pixel_count += child->pixel_count;
        removed += 1;
        child = nullptr;
    }

    return removed;
}