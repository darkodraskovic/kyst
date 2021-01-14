#version 330 core

#include Lib/uniform.glsl
#include Lib/attribute.glsl
#include Lib/function.glsl

out vec3 vFragPos;
out vec3 vFragNorm;

void main()
{
    gl_Position = project3D(aPos);
    vFragPos = fragPos3D(aPos);
    vFragNorm = fragNorm(aNorm);
}
