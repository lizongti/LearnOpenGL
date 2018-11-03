#version 330 core
layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_tex_coord;

out vec2 vert_tex_coord;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(in_pos, 1.0f);
    vert_tex_coord = vec2(in_tex_coord.x, in_tex_coord.y);
}