#pragma once

#include "utility.h"

extern vector3 camera_position;

extern float field_of_view;

typedef struct vertex {
    vector3 position;
} vertex;
#define Vertex(vec) (vertex){vec}

typedef struct triangle {
    vertex vertices[3];
} triangle;


vector2 screen_space(vector3 position);

vector3 view_space(vector3 world_position);

void drawTriangle(triangle tri);
