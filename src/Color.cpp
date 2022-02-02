#include "Color.h"
#include <iostream>

Color::Color(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

// Copy constructor
Color::Color(const Color &col) {
    r = col.r;
    g = col.g;
    b = col.b;
}

void Color::print() {
    std::cout << "RGB: " << r << ", " << g << ", " << b << "\n";
}

void Color::add(Color other) {
    this->r += other.r;
    this->g += other.g;
    this->b += other.b;
}

Color Color::div(int k) {
    Color col(this->r / k, this->g / k, this->b / k);
    return col;
}