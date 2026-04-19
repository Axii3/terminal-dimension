#include <stdio.h>

#define SIZEOF(arr) sizeof(arr) / sizeof(*arr)

#define WIDTH 5
#define HEIGHT 5

int display_size = WIDTH * HEIGHT;
int display[WIDTH * HEIGHT];

char char_dictionary[] = {'.', '#'};

void draw();
void setPixel(int x, int y, int value);

//remove
int len(int array[]) {
	return sizeof(*array) / sizeof(array[0]);
}

int main() {

	setPixel(0, 0, 5);
	setPixel(2, 2, 1);

	draw();

	return 0;
}

void draw(){
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
        	{
        		int list_space = display[(y * WIDTH) + x];
        		if (list_space <= SIZEOF(char_dictionary)){
        			printf("%c", char_dictionary[list_space]);
        		}
        		else {
        			printf("%c", 'o');
        		}
        		

                //printf("\033[0m. ");
            }
        }
        printf("\033[0m\n");
    }
    return;
}

void setPixel(int x, int y, int value) {
	display[(y * WIDTH) + x] = value;
}