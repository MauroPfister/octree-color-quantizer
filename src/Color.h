#pragma once

struct Color {
    int r;
    int g;
    int b;

    Color(int r, int g, int b);
    Color (const Color &old_col); 
    void print();
    void add(Color other);
    Color div(int x);
    void normalize();
};