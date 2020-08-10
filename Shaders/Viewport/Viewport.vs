#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec3 vPos;
out vec2 vTexCoords;

void main()
{
    vTexCoords = aTexCoords;
    vPos = vec3(aPos.xy, 1);
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}
