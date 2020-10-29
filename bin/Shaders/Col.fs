#version 330 core

#include Lib/uniform.glsl

out vec4 FragColor;

void main()
{
    FragColor = vec4(uColor, uAlpha);
}
