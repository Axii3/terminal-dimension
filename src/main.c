#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "display.h"
#include "utility.h"
#include "vertex_shader.h"

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


int player_x = 0;
int player_y = 0;

struct triangle t1 = (triangle){
		Vertex(Vector3(5, 5, 0)), 
		Vertex(Vector3(60, 5, 0)), 
		Vertex(Vector3(15, 30, 0))};

void update(char key);

//remove
int len(int array[]) {
	return sizeof(*array) / sizeof(array[0]);
}

int main() {
	struct termios orig_termios;
    enableRawMode(&orig_termios);

    // set to non blocking mode
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

	int running = 1;
	while(running){
		char c;
        if (read(STDIN_FILENO, &c, 1) == 1) {
            if (c == 'x') break;
        }else {
        	c = '\0';
        }

        update(c);

        system("clear");
        draw();
        clear();

	}
	disableRawMode(&orig_termios);
	return 0;
}

void update(char key) {
	//printf("%c", key);


	if (key == 'd'){
		player_x++;
	}
	else if(key == 'a'){
		player_x --;
	}
	else if (key == 'w'){
		player_y++;
	}
	else if(key == 's'){
		player_y --;
	}

	drawTriangle(t1);
}

