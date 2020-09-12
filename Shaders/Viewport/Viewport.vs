#version 330 core

#include ../Lib/transform.glsl
#include ../Lib/attribute.glsl

out vec3 vPos;
out vec2 vTexCoord;

void main()
{
    vPos = vec3(aPos.xy, 1);
    vTexCoord = aTexCoord;
    gl_Position = uModel * vec4(aPos.x, aPos.y, 0.0, 1.0);
}
