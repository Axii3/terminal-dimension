#include "vertex_shader.h"
#include "display.h"

void drawTriangle(triangle tri) {
    drawLine(screen_space(tri.vertices[0].position), screen_space(tri.vertices[1].position), 1);
}

vector2 screen_space(vector3 position)  {
	vector2 ss_pos;
	ss_pos.x = position.x;
	ss_pos.y = position.y;
	return ss_pos;
}