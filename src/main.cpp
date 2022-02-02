#include <iostream>
#include <cstdlib>
#include "Color.h"
#include "Node.h"
#include "ColorOctree.h"

#define cimg_display 0
#define cimg_use_jpeg 1

#include "CImg.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char **argv) {
    CImg<float> image;
    string filePath = "data/parrot.jpg";
    int n_colors = 50;

    if (argc > 1) {
        n_colors = std::atoi(argv[1]);
    }

    image.load(filePath.c_str());
    int w = image.width();
    int h = image.height();

    Color col(0, 0, 0);
    ColorOctree tree;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            col.r = image(i, j, 0);
            col.g = image(i, j, 1);
            col.b = image(i, j, 2);
            tree.add_color(col);
        }
    }
    tree.reduce_tree(n_colors);

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            col.r = image(i, j, 0);
            col.g = image(i, j, 1);
            col.b = image(i, j, 2);
            Color new_col = tree.get_palette_color(col);
            image(i, j, 0) = new_col.r;
            image(i, j, 1) = new_col.g;
            image(i, j, 2) = new_col.b;
        }
    }

    image.save("data/parrot_quantized.jpg");

    std::cout << "Done!\n";

    return 0;
}