#version 330 core

#include Lib/transform.glsl

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 vCol;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    vCol = aCol;
}
