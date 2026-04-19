#pragma once



typedef struct vector2 {
    float x;
    float y;
} vector2;

typedef struct vector3 {
    float x;
    float y;
    float z;
} vector3;

#define Vector2(x, y) (vector2){x, y}
#define Vector3(x, y, z) (vector3){x, y, z}