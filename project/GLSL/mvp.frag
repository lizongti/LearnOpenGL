#version 330 core
out vec4 frag_color;

in vec2 vert_tex_coord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    frag_color = mix(texture(texture1, vert_tex_coord), texture(texture2, vert_tex_coord), 0.2);
}