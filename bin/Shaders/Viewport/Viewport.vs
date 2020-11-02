#version 330 core

#include ../Lib/transform.glsl
#include ../Lib/attribute.glsl

out vec2 vTexCoord;

void main()
{
    vTexCoord = aTexCoord;
    gl_Position = uModel * vec4(aPos.x, aPos.y, 0.0, 1.0);
}
