#version 330 core

#include Lib/uniform.glsl
#include Lib/attribute.glsl
#include Lib/function.glsl

out vec3 vFragPos;
out vec3 vFragNorm;
out vec2 vTexCoord;

void main()
{
    vFragPos = fragPos3D(aPos);
    vFragNorm = fragNorm(aNorm);
    vTexCoord = aTexCoord.xy;

    gl_Position = project3D(aPos);
}
