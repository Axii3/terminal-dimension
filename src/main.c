#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void enableRawMode(struct termios *orig_termios) {
    struct termios raw;

    tcgetattr(STDIN_FILENO, orig_termios); // save original settings
    raw = *orig_termios;

    raw.c_lflag &= ~(ICANON | ECHO); // disable canonical mode & echo
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode(struct termios *orig_termios) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

#define WIDTH 160
#define HEIGHT 40

#define SIZEOF(arr) sizeof(arr) / sizeof(*arr)
#define GET_ONED_POSITION(x, y) (y * WIDTH) + x

int display_size = WIDTH * HEIGHT;
int display[WIDTH * HEIGHT];

char char_dictionary[] = {' ', '#'};

typedef struct{
	int x;
	int y;
} Vector2;
#define Vector2(x, y) (Vector2){x, y}


int player_x = 0;
int player_y = 0;

int getPixel(Vector2 position);
void setPixel(Vector2 position, int value);
void drawLine(Vector2 position1, Vector2 position2, int value);
void clear();
void draw();

void update(char key);

//remove
int len(int array[]) {
	return sizeof(*array) / sizeof(array[0]);
}

int main() {
	struct termios orig_termios;
    enableRawMode(&orig_termios);

	//setPixel(Vector2(0, 0), 5);
	//setPixel(Vector2(5, 5), 1);
	drawLine(Vector2(19,19), Vector2(4,2), 1);
	drawLine(Vector2(4,19), Vector2(19,2), 1);

	int running = 1;
	while(running){
		char c;
        if (read(STDIN_FILENO, &c, 1) == 1) {
            if (c == 'x') break;
        }

        update(c);

        draw();
        clear();

	}
	disableRawMode(&orig_termios);
	return 0;
}

void update(char key) {
	printf("%c", key);


	if (key == 'd'){
		player_x++;
  		if (player_x > WIDTH) player_x = WIDTH;
	}
	else if(key == 'a'){
		player_x --;
		if (player_x < 0) player_x = 0;
	}
	else if (key == 'w'){
		player_y++;
  		if (player_y > HEIGHT) player_y = HEIGHT;
	}
	else if(key == 's'){
		player_y --;
		if (player_y < 0) player_y = 0;
	}
	drawLine(Vector2(4,19), Vector2(player_x,player_y), 1);
}

void draw(){
	system("clear");
    printf("\e[1;1H\e[2J"); 
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

void clear() {
	for (int i = 0; i < SIZEOF(display); ++i)
	{
		display[i] = 0;
	}
}

void setPixel(Vector2 position, int value) {
	display[GET_ONED_POSITION(position.x, position.y)] = value;
}

int getPixel(Vector2 position) {
	return display[GET_ONED_POSITION(position.x, position.y)];
}

void drawLine(Vector2 position1, Vector2 position2, int value) {

	Vector2 start;
	Vector2 end;
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