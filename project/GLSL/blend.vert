#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoords;


uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
    
    gl_Position = projection * view * vec4(vec3(instanceMatrix * vec4(aPos, 1.0)), 1.0);
}