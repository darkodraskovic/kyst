#version 330 core

#include Lib/transform.glsl

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aCol;

out vec3 vCol;
out vec2 vTexCoord;
out vec3 vPos;

void main()
{
    vCol = aCol;
    vTexCoord = aTexCoord;
    vPos = vec3(aPos.xy, 1);
    gl_Position = uProjection * uView * uModel * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
