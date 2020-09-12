#version 330 core

#include Lib/uniform.glsl

in vec3 vCol;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vCol, uAlpha);
}
