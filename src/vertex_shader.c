#include "vertex_shader.h"
#include "display.h"

vector3 camera_position = Vector3(0, 0, 0);

float field_of_view = 100;

void drawTriangle(triangle tri) {
    
    int v = 0;
    for (int t = 0; t < 3; ++t) {
        
        vector2 point1 = screen_space(view_space(tri.vertices[v].position));
        if (v == 2) { v = 0; }else {v++;}
        vector2 point2 = screen_space(view_space(tri.vertices[v].position));

        drawLine(point1, point2, 1);
    }

}

vector2 screen_space(vector3 position)  {
	vector2 ss_pos;
	ss_pos.x = (WIDTH/2) + ((position.x * field_of_view) / (position.z + field_of_view));
	ss_pos.y = (HEIGHT/2) - ((position.y * field_of_view) / (position.z + field_of_view));
	return ss_pos;
}

vector3 view_space(vector3 world_position) {
    vector3 vs_pos;
    vs_pos.x = world_position.x - camera_position.x;
    vs_pos.y = world_position.y - camera_position.y;
    vs_pos.z = world_position.z - camera_position.z;
    return vs_pos;
}