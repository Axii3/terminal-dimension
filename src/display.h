#pragma once

#include <stdio.h>
#include "utility.h"

#define WIDTH 160
#define HEIGHT 40

#define SIZEOF(arr) sizeof(arr) / sizeof(*arr)
#define GET_ONED_POSITION(x, y) (int)((y * WIDTH) + x)

extern int display_size;
extern int display[];

extern char char_dictionary[];




int getPixel(vector2 position);

void setPixel(vector2 position, int value);

void drawLine(vector2 position1, vector2 position2, int value);

void clear();

void draw();
