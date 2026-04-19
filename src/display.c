#include <stdio.h>
#include "display.h"
#include "utility.h"



int display_size = WIDTH * HEIGHT;
int display[WIDTH * HEIGHT];

char char_dictionary[] = {' ', '#'};



void draw(){
	
    printf("\e[1;1H\e[2J"); 
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
        	{
        		vector2 position = Vector2(x, y);
        		if (getPixel(position) <= SIZEOF(char_dictionary)){
        			printf("%c", char_dictionary[getPixel(position)]);
        		}
        		else {
        			printf("%c", 'o');
        		}
            }
        }
        printf("\033[0m\n");
    }
    return;
}

void clear() {
	for (int i = 0; i < SIZEOF(display); ++i)
	{
		display[i] = 0;
	}
}

void setPixel(vector2 position, int value) {
	if (position.x > WIDTH) {
		return;
	}
	if (position.x < 0) {
		return;
	}
	if (position.y > HEIGHT) {
		return;
	}
	if (position.y < 0) {
		return;
	}
	display[GET_ONED_POSITION(position.x, position.y)] = value;
}

int getPixel(vector2 position) {
	return display[GET_ONED_POSITION(position.x, position.y)];
}

void drawLine(vector2 position1, vector2 position2, int value) {

	vector2 start;
	vector2 end;
	if (position2.x > position1.x) {
		start = position1;
		end = position2;
	} else {
		start = position2;
		end = position1;
	}

	int width = end.x - start.x;
	int height = end.y - start.y;

	float m = (float)height / width;
	for (int x = 0; x < width; ++x)
	{
		int y = (int)(m * x) + start.y;
		setPixel(Vector2(start.x + x, y), value);
	}
}