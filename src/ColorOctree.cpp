#include <iostream>
#include "ColorOctree.h"
#include "Color.h"

ColorOctree::ColorOctree()
    : root(new Node(0))
    , n_nodes(0)
    , n_leaves(0)
    {
}

// Add a color to the octree.
void ColorOctree::add_color(Color col) {
    Node *parent = root;
    Node *child = nullptr;

    int index = 0;
    for (int level = 0; level < MAX_LEVEL; level++) {
        index = index_at_level(col, level);
        child = parent->children[index];

        if (child == nullptr) {
            n_nodes += 1;
            Node *new_node = new Node(n_nodes);
            levels[level].push_back(new_node);

            if (level >= MAX_LEVEL - 1) {
                new_node->color = col;
                new_node->pixel_count += 1;
                n_leaves += 1;
            }
            parent->children[index] = new_node;
        }
        else if (child->is_leaf()) {
            child->color.add(col);
            child->pixel_count += 1;
        }
        parent = parent->children[index];
    }
}

// Compute index of child node at a given level.
int ColorOctree::index_at_level(Color col, int level) {
    int index = 0;
    int bit_mask = 0x80 >> level;

    if (col.r & bit_mask) {
        index += 4;
    }
    if (col.g & bit_mask) {
        index += 2;
    }
    if (col.b & bit_mask) {
        index += 1;
    }

    return index;
}

// Reduce the number of leaf nodes in octree until fewer than k.
void ColorOctree::reduce_tree(int k) {
    // Start on second last level because last level by construction only contains leaf nodes.

    for (int level = MAX_LEVEL - 2; level >= 0; level--) {
        // TODO: Sort nodes on level based on their pixel count.
        // See: http://www.emsr-design.de/fil/graph/A_simple_method_for_color_quantization_o.pdf
        for (Node *node : levels[level]) {
            n_leaves -= node->remove_children();
            if (n_leaves <= k) {
                std::cout << n_leaves << std::endl;
                return;
            }
        }
    }
}

// Get palette color representing query color in image.
Color ColorOctree::get_palette_color(Color col) {
    Node *parent = root;
    Node *child = nullptr;
    int index;

    for (int level = 0; level < MAX_LEVEL; level++) {
        index = index_at_level(col, level);
        child = parent->children[index];

        if (child->is_leaf()) {
            return child->avg_color();
        }
        else {
            parent = child;
        }
    }
}


/*

    def get_palette_color(self, color):
        """Get palette color representing query color in image."""
        parent = self.root
        for level in range(self.MAX_LEVEL):
            index = self.index_at_level(color, level)
            child = parent.children[index]
            
            if child.is_leaf():
                return child.avg_color()
            else:
                parent = child

    def add_children_to_graph(self, g, node):
        """Recursively add children of node to graph visualization."""
        for child in node.children:
            if child is not None:
                color = child.color.div(max(1 , child.pixel_count)).normalize().to_tuple()
                g.add_vertex(name=child.id, color=color)
                g.add_edge(node.id, child.id, color=color)
                self.add_children_to_graph(g, child)
    
    def visualize(self, file_name):
        """Visualize octree as a graph."""
        g = Graph()
        g.add_vertex(name=self.root.id, 
                     color=self.root.color.to_tuple())
        self.add_children_to_graph(g, self.root)
        lay = g.layout("rt_circular", root=0)
        plot(g, layout=lay, bbox=(0, 0, 2000, 2000), margin=100, target=file_name)

    @staticmethod
    def index_at_level(color, level):
        """Compute index of child node at a given level."""
        index = 0
        bit_mask = 0b10000000 >> level
        if color.r & bit_mask:
            index += 4
        if color.g & bit_mask:
            index += 2
        if color.b & bit_mask:
            index += 1
        
        return index
*/