#version 330 core

#include Lib/transform.glsl

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out vec3 vFragPos;
out vec3 vFragNorm;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    vFragPos = mat3(uModel) * aPos;
    vFragNorm = mat3(transpose(inverse(uModel))) * aNorm;
}
