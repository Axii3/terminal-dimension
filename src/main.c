#include <stdio.h>

#define WIDTH 40
#define HEIGHT 20

#define SIZEOF(arr) sizeof(arr) / sizeof(*arr)
#define GET_ONED_POSITION(x, y) (y * WIDTH) + x

int display_size = WIDTH * HEIGHT;
int display[WIDTH * HEIGHT];

char char_dictionary[] = {'.', '#'};

typedef struct{
	float x;
	float y;
} Vector2;
#define Vector2(x, y) (Vector2){x, y}

int getPixel(Vector2 position);
void setPixel(Vector2 position, int value);


void draw();


//remove
int len(int array[]) {
	return sizeof(*array) / sizeof(array[0]);
}

int main() {

	setPixel(Vector2(0, 0), 5);
	setPixel(Vector2(5, 5), 1);

	draw();

	return 0;
}

void draw(){
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
        	{
        		Vector2 position = Vector2(x, y);
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

void setPixel(Vector2 position, int value) {
	display[GET_ONED_POSITION((int)position.x, (int)position.y)] = value;
}

int getPixel(Vector2 position) {
	return display[GET_ONED_POSITION((int)position.x, (int)position.y)];
}