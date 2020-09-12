#version 330 core

#include Lib/transform.glsl

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aTexCoord;

out vec3 vFragPos;
out vec3 vFragNorm;
out vec2 vTexCoords;

void main()
{
    vFragPos = mat3(uModel) * aPos;
    vFragNorm = mat3(transpose(inverse(uModel))) * aNorm;
    vTexCoords = aTexCoord.xy;

    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
