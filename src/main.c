#include <stdio.h>
#include <stdlib.h>
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


vector3 player_position = Vector3(0, 0, -5);
float player_speed = 10;

struct triangle t1 = (triangle){
		Vertex(Vector3(0, 0, 0)), 
		Vertex(Vector3(0, 25, 0)), 
		Vertex(Vector3(50, 0, 0))};

struct triangle t2 = (triangle){
		Vertex(Vector3(0, 25, 0)), 
		Vertex(Vector3(50, 25, 0)),
		Vertex(Vector3(50, 0, 0))};

struct triangle t3 = (triangle){
		Vertex(Vector3(0, 0, 50)), 
		Vertex(Vector3(0, 25, 50)), 
		Vertex(Vector3(50, 0, 50))};

struct triangle t4 = (triangle){
		Vertex(Vector3(0, 25, 50)), 
		Vertex(Vector3(50, 25, 50)), 
		Vertex(Vector3(50, 0, 50))};



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
		player_position.x++;
	}
	else if(key == 'a'){
		player_position.x--;
	}
	else if (key == ' '){
		player_position.y++;
	}
	else if(key == 'c'){
		player_position.y--;
	}
	else if (key == 'w'){
		player_position.z++;
	}
	else if(key == 's'){
		player_position.z--;
	}
	else if (key == 'e'){
		field_of_view++;
	}
	else if(key == 'q'){
		field_of_view--;
	}

	camera_position = player_position;

	drawTriangle(t1);
	drawTriangle(t2);
	drawTriangle(t3);
	drawTriangle(t4);
	//drawLine(Vector2(40, 0), Vector2(player_position.x, player_position.y), 1);
}

