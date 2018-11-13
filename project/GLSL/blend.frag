#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D transparent;

void main()
{             
    //vec4 color = texture(texture3, TexCoords);
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    //vec4 color = texture(transparent, vec2(0.5, 0.5));
    //FragColor = texture(transparent, TexCoords);
}