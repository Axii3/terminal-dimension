#pragma once

#include "utility.h"

typedef struct vertex {
    vector3 position;
} vertex;
#define Vertex(vec) (vertex){vec}

typedef struct triangle {
    vertex vertices[3];
} triangle;

void drawTriangle(triangle tri);

vector2 screen_space(vector3 position);