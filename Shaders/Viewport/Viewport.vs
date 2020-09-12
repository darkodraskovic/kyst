#version 330 core

uniform mat4 uModel = mat4(1.f);

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 vPos;
out vec2 vTexCoords;

void main()
{
    vPos = vec3(aPos.xy, 1);
    vTexCoords = aTexCoord;
    gl_Position = uModel * vec4(aPos.x, aPos.y, 0.0, 1.0);
}
