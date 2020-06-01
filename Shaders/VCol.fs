#version 330 core

uniform float uAlpha;

in vec3 vCol;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vCol, uAlpha);
}
